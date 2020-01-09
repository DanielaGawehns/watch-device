#ifndef __watch_svc_data__
#define __watch_svc_data__
 
#include <stdint.h>
 
#define HEADER_MAGIC (0xC001DA7A)
#define CONFIG_MAGIC (0x0DA7ACF6)
 
#define QUANT_TYPE_SCALAR (0)
#define QUANT_TYPE_VECTOR (1)
 
/**
 * Represents a data point of a quantity at a point in time
 */
typedef struct {

    /**
     * Checksum over the data point.
     * Computed using the CRC32 algorithm, with this field
     * set to zero for the calculation.
     */
    uint32_t      checksum;
 
    
    /**
     * Data timestamp
     * Unit: milliseconds since 00:00 January 1st 1970
     */
    long long int timestamp;
 
 
    /**
     * The value, either a scalar or a vector
     */
    union {
        struct {
            double x, y, z;
        };
        double s;
    } value;
 
    /**
     * Measurement type id that describes the data layout of this measurement
     */
    int measurement_type_id;
 
} measurement_t;
 

/**
 * Measurement type descriptor
 */
typedef struct {
    /**
     * The quantity ID.
     */
    int           id;
 
    /**
     * The data storage type.
     * One of the MEAS_TYPE_* constants.
     */
    int           type;
 
    /**
     * The quantity name.
     * Zero-terminated C string.
     */
    char          name[128];
 
    /**
     * The unit this quantity is measured in.
     * Zero-terminated C string.
     */
    char          unit[128];
 
} measurement_type;
 
typedef struct {
 
    /**
     * Magic number.
     * Used to recognize the start of a data record, in case
     * we lose sync (malformed or truncated data) we can resync
     * on this.
     * Should always be set to HEADER_MAGIC
     */
    uint32_t      magic;
 
    /**
     * The reference name for the measurement run.
     * This value is set in the measurement configuration
     * and, together with the timestamps, serves to identify
     * the measurement session.
     */
    char          reference[128];
 
    /**
     * The start time for the data described by this header.
     * Unit: milliseconds since 00:00 January 1st 1970
     */
    long long int time_start;
 
    /**
     * The end time for the data described by this header.
     * Unit: milliseconds since 00:00 January 1st 1970
     */
    long long int time_end;
 
    /**
     * The number of quantities measured
     */
    int           nquant;
 
    /**
     * Data point count
     */
    int           ndata;
 
    /**
     * Quantity entry size
     */
    unsigned int  quant_sz;
 
    /**
     * Measurement size
     */
    unsigned int  meas_sz;
 
    /**
     * Checksum over the header.
     * Computed using the CRC32 algorithm, with this field
     * set to zero for the calculation.
     */
    uint32_t      checksum;
 
    /**
     * Quantity information
     */
    quantity_t    quant[0];
 
} dataheader_t;
 
#define CONFIG_MAGIC (0x0DA7ACF6)
 
typedef struct {
 
    /**
     * Magic number.
     * Used to recognize the start of a config file.
     * Should always be set to CONFIG_MAGIC
     */
    uint32_t      magic;
 
    /**
     * The reference name for the measurement run.
     * This value will be recorded in the measurement data
     * and, together with the timestamps, serves to identify
     * the measurement session.
     */
    char          reference[128];
 
    /**
     * The start time for the measurements requested
     * Unit: milliseconds since 00:00 January 1st 1970
     */
    long long int time_start;
 
    /**
     * The end time for the measurement run.
     * Unit: milliseconds since 00:00 January 1st 1970
     */
    long long int time_end;
 
    /**
     * The number of quantities measured
     */
    int           nquant;
 
    /**
     * Quantity entry size
     */
    unsigned int  quant_sz;
 
    /**
     * Checksum over the config.
     * Computed using the CRC32 algorithm, with this field
     * set to zero for the calculation.
     */
    uint32_t      checksum;
 
    /**
     * Quantity information
     */
    quantity_t    quant[0];
 
} measconfig_t;
 
#define QUANTITY_IN_CONFIG( Co, Num ) ( (quantity_t *) (((void*)Co->quant) + Co->quant_sz * Num)  )
#define QUANTITY_IN_HEADER( Co, Num ) ( (quantity_t *) (((void*)Co->quant) + Co->quant_sz * Num)  )
 
#endif