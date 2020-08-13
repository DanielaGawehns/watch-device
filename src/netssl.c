/**
 * @file network.c
 * @author Peter Bosch <me@pbx.sh>
 * @brief Low-Level networking code
 */

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "network.h"
#include <openssl/ssl.h>
#include <openssl/bio.h>

extern struct sockaddr_in srv_addr;
#define TRUSTSTORE_PATH   ("watch.pem")
#define PREFERRED_CIPHERS ("HIGH:!aNULL:!kRSA:!PSK:!SRP:!MD5:!RC4")

static SSL        * ssl = NULL;
static SSL_CTX    * ssl_ctx = NULL;
static BIO        * ssl_conn = NULL;
//static BIO_ADDR   * ssl_addr = NULL;
extern int    clnt_sock;

void ssl_log_err (const char *fmt);

int client_ssl_verify(int preverify, X509_STORE_CTX* x509_ctx)
{
    int depth = X509_STORE_CTX_get_error_depth(x509_ctx);
    int err = X509_STORE_CTX_get_error(x509_ctx);
    
    X509* cert = X509_STORE_CTX_get_current_cert(x509_ctx);
    X509_NAME* iname = cert ? X509_get_issuer_name(cert) : NULL;
    X509_NAME* sname = cert ? X509_get_subject_name(cert) : NULL;
    
    //print_cn_name("Issuer (cn)", iname);
    //print_cn_name("Subject (cn)", sname);
    
    if(depth == 0) {
        /* If depth is 0, its the server's certificate. Print the SANs too */
      //  print_san_name("Subject (san)", cert);
    }

    return preverify;
}

int client_init() {
  int res;
  const SSL_METHOD *method;

  SSL_library_init();
  method = SSLv23_method();

	if ( !method ) {
		net_log_err( "Failed to create SSLv23 method");
		return -1;
	}

  ssl_ctx = SSL_CTX_new( method );

	if ( !ssl_ctx ) {
		ssl_log_err( "Failed to create OpenSSL context %s");
		return -1;
	}

  SSL_CTX_set_verify      ( ssl_ctx, SSL_VERIFY_PEER, client_ssl_verify);
  SSL_CTX_set_verify_depth( ssl_ctx, 4 );
  SSL_CTX_set_options( ssl_ctx, 
      SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3 | SSL_OP_NO_COMPRESSION );

  res = SSL_CTX_load_verify_locations( ssl_ctx, TRUSTSTORE_PATH, NULL );
  if ( res != 1 ) {
		ssl_log_err( "Failed to load trust store %s");
		return -1;
	}
/*
  ssl_addr = BIO_ADDR_new();

	if ( !ssl_addr ) {
		net_log_err( "Failed to create OpenSSL address");
		return -1;
	}*/

}
void ssl_log_err (const char *fmt)
{ BIO *bio = BIO_new (BIO_s_mem ());
  //ERR_print_errors (bio);
  char *buf = NULL;
  size_t len = BIO_get_mem_data (bio, &buf);
  char *ret = (char *) calloc (1, 1 + len);
  if (ret)
    memcpy (ret, buf, len);
  BIO_free (bio);
	net_log_err(fmt, ret);
  free(ret);
}


int client_connect() {
	int r;
    struct timeval timeout;
	clnt_sock = socket( AF_INET, SOCK_STREAM, 0 );

	if ( clnt_sock < 0 ) {
		net_log_err( "Failed to open TCP socket: %s (%i)",
				strerror(errno), errno);
		return -1;
	}

	r = fcntl( clnt_sock, F_SETFL, 0 );

	if ( r < 0 ) {
		net_log_err( "Failed to blocking mode: %s (%i)",
				strerror(errno), errno);
		close( clnt_sock );
		return -1;
	}

	timeout.tv_sec = 1;
	timeout.tv_usec = 750000;

	r = setsockopt( clnt_sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

	if ( r < 0 ) {
		net_log_err( "Failed to set timeout: %s (%i)",
				strerror(errno), errno);
		close( clnt_sock );
		return -1;
	}

	r = connect( clnt_sock, 
	             (struct sockaddr *) &srv_addr, sizeof srv_addr );

	if ( r < 0 ) {
		net_log_err( "Failed to connect TCP socket: %s (%i)",
					strerror(errno), errno);
		return -1;
	}

	ssl_conn = BIO_new_socket( clnt_sock, BIO_NOCLOSE );

	ssl = SSL_new( ssl_ctx );
	if ( !ssl ) {
		ssl_log_err( "Failed to get SSL object: %s");
		client_close();
		return -1;
	}

	SSL_set_bio( ssl, ssl_conn, ssl_conn );
  
	r = SSL_set_cipher_list( ssl, PREFERRED_CIPHERS );
	if ( !ssl ) {
		ssl_log_err( "Failed to set SSL ciphers: %s");
		client_close();
		return -1;
	}

  //TODO: set_tlsext_host_name

	r = SSL_connect( ssl );
	if ( r < 0 ) {
		ssl_log_err( "Failed to connect SSL object: %s");
		client_close();
		return -1;
	}

  //TODO: verify certificate

	return 0;

}


void client_close() {
	//TODO: implement this
}

int client_write( const void *data, size_t size ) {
	ssize_t ws, off;
	for ( off = 0; off < size; off += ws ) {
		ws = SSL_write( ssl, data + off, size - off );
		if ( ws < 0 ) {
			ssl_log_err( "Failed to send data over SSL: %s");
			client_close();
			return -1;
		}
	}
	return 0;
}

int client_available( ) {
	char foo;
	int err, r;
	r = SSL_read( ssl, &foo, 0 );
	if ( r < 0 ) {
		err = SSL_get_error( ssl, r );
		if ( err != SSL_ERROR_SYSCALL && 
             err != SSL_ERROR_WANT_READ &&
             err != SSL_ERROR_WANT_WRITE )
			return -1;
		
		if ( err == SSL_ERROR_SYSCALL && 
			 errno != EAGAIN )
			return -1;			 
	}
	return SSL_pending( ssl );
}


/**
 * 
 *
 *
 */
int client_read( void *data, size_t size ) {
	ssize_t ws, off;
	for ( off = 0; off < size; off += ws ) {
		ws = SSL_read( ssl, data + off, size - off );
		if ( ws < 0 && errno == EINTR ) {
			ssl_log_err( "Failed to receive data over SSL: %s (%i)");
			client_close();
			return -1;
		} else if ( ws < 0 )
			ws = 0;
	}
	return 0;
}

