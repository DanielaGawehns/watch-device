S/W Version Information
Model: SM-R365
Tizen-Version: 2.3.1.13
Build-Number: R365XXU2CRC7
Build-Date: 2018.03.27 20:26:45

Crash Information
Process Name: sensorbasicui
PID: 8683
Date: 2019-10-24 19:05:59+0900
Executable File Path: /opt/usr/apps/org.example.sensorbasicui/bin/sensorbasicui
Signal: 6
      (SIGABRT)
      si_code: -6
      signal sent by tkill (sent by pid 8683, uid 5000)

Register Information
r0   = 0x00000000, r1   = 0x000021eb
r2   = 0x00000006, r3   = 0x000021eb
r4   = 0x00000006, r5   = 0x000f5528
r6   = 0x404d4bec, r7   = 0x0000010c
r8   = 0x42f961a0, r9   = 0x00000002
r10  = 0x0000007a, fp   = 0xbefdac78
ip   = 0x42f96660, sp   = 0xbefda540
lr   = 0x403df6bc, pc   = 0x403db9e8
cpsr = 0x20000010

Memory Information
MemTotal:   490988 KB
MemFree:      6072 KB
Buffers:     58860 KB
Cached:     150352 KB
VmPeak:     103676 KB
VmSize:     102936 KB
VmLck:           0 KB
VmPin:           0 KB
VmHWM:       16960 KB
VmRSS:       16956 KB
VmData:      47504 KB
VmStk:         136 KB
VmExe:          16 KB
VmLib:       24852 KB
VmPTE:          54 KB
VmSwap:          0 KB

Threads Information
Threads: 7
PID = 8683 TID = 8683
8683 8692 8693 8694 8705 8706 8707 

Maps Information
40000000 40004000 r-xp /opt/usr/apps/org.example.sensorbasicui/bin/sensorbasicui
40006000 4000a000 r-xp /usr/lib/libsys-assert.so
40014000 40031000 r-xp /lib/ld-2.13.so
4003b000 4003e000 r-xp /usr/lib/libnative-buffer.so.0.1.0
40047000 4004a000 rw-p [stack:8707]
4004d000 4004f000 r-xp /usr/lib/libcapi-appfw-app-common.so.0.3.2.5
40058000 4005c000 r-xp /usr/lib/libcapi-appfw-application.so.0.3.2.5
40064000 4006a000 r-xp /usr/lib/libcapi-base-common.so.0.1.8
40073000 40077000 r-xp /usr/lib/libcapi-system-sensor.so.0.1.18
40080000 40088000 r-xp /usr/lib/libcapi-system-system-settings.so.0.0.2
40089000 4008b000 r-xp /usr/lib/libdlog.so.0.0.0
40093000 400aa000 r-xp /usr/lib/libecore.so.1.7.99
400c1000 400e2000 r-xp /usr/lib/libefl-extension.so.0.1.0
400eb000 40225000 r-xp /usr/lib/libelementary.so.1.7.99
4023c000 4030a000 r-xp /usr/lib/libevas.so.1.7.99
40330000 403a5000 r-xp /usr/lib/libsqlite3.so.0.8.6
403af000 404ca000 r-xp /lib/libc-2.13.so
404d8000 404e0000 r-xp /lib/libgcc_s-4.6.so.1
404e1000 404ec000 r-xp /lib/libunwind.so.8.0.1
40519000 4051b000 r-xp /lib/libdl-2.13.so
40524000 40530000 r-xp /usr/lib/libaul.so.0.1.0
4053a000 4055d000 r-xp /usr/lib/libpkgmgr-info.so.0.0.17
40565000 40579000 r-xp /lib/libpthread-2.13.so
40584000 40588000 r-xp /usr/lib/libcapi-appfw-app-control.so.0.3.2.5
40591000 40596000 r-xp /usr/lib/libappcore-efl.so.1.1
4059e000 405a3000 r-xp /usr/lib/libappcore-common.so.1.1
405ab000 405ec000 r-xp /usr/lib/libeina.so.1.7.99
405f5000 4061f000 r-xp /usr/lib/libsensor.so.2.3.4
40628000 406bc000 r-xp /usr/lib/libstdc++.so.6.0.16
406cf000 40738000 r-xp /lib/libm-2.13.so
40741000 40791000 r-xp /usr/lib/libecore_x.so.1.7.99
40793000 407b5000 r-xp /usr/lib/libecore_evas.so.1.7.99
407be000 407c7000 r-xp /usr/lib/libvconf.so.0.2.45
407cf000 407f7000 r-xp /usr/lib/libfontconfig.so.1.8.0
407f8000 408c4000 r-xp /usr/lib/libxml2.so.2.7.8
408d1000 409a1000 r-xp /usr/lib/libglib-2.0.so.0.3200.3
409a2000 409b4000 r-xp /usr/lib/libefl-assist.so.0.1.0
409bc000 409c2000 r-xp /lib/librt-2.13.so
409cb000 40a29000 r-xp /usr/lib/libedje.so.1.7.99
40a32000 40aea000 r-xp /usr/lib/libcairo.so.2.11200.14
40af5000 40bd6000 r-xp /usr/lib/libX11.so.6.3.0
40be1000 40bea000 r-xp /usr/lib/libXi.so.6.1.0
40bf2000 40c0b000 r-xp /usr/lib/libeet.so.1.7.99
40c1c000 40c21000 r-xp /usr/lib/libecore_file.so.1.7.99
40c29000 40c3a000 r-xp /usr/lib/libecore_input.so.1.7.99
40c42000 40c4b000 r-xp /usr/lib/libedbus.so.1.7.99
40c53000 40c7d000 r-xp /usr/lib/libdbus-1.so.3.8.12
40c86000 40ca0000 r-xp /usr/lib/libecore_con.so.1.7.99
40ca9000 40cbc000 r-xp /usr/lib/libfribidi.so.0.3.1
40cc4000 40d01000 r-xp /usr/lib/libharfbuzz.so.0.940.0
40d0a000 40d60000 r-xp /usr/lib/libfreetype.so.6.11.3
40d6d000 40dc3000 r-xp /usr/lib/libpixman-1.so.0.28.2
40dd0000 40dd3000 r-xp /usr/lib/libbundle.so.0.1.22
40ddb000 40df2000 r-xp /usr/lib/libdbus-glib-1.so.2.2.2
40dfa000 40dff000 r-xp /usr/lib/libxdgmime.so.1.1.0
40e07000 40e43000 r-xp /usr/lib/libsystemd.so.0.4.0
40e4d000 40e51000 r-xp /usr/lib/libproc-stat.so.0.2.86
40e5a000 40e70000 r-xp /usr/lib/libpkgmgr_parser.so.0.1.0
40e79000 40e7f000 r-xp /usr/lib/libappsvc.so.0.1.0
40e87000 40e8d000 r-xp /usr/lib/libecore_imf.so.1.7.99
40e95000 40ec9000 r-xp /usr/lib/libgobject-2.0.so.0.3200.3
40ed3000 40ed5000 r-xp /usr/lib/libiniparser.so.0
40ede000 40fb1000 r-xp /usr/lib/libgio-2.0.so.0.3200.3
40fbc000 40fc6000 r-xp /usr/lib/libsensord-shared.so
40fcf000 40fd6000 r-xp /usr/lib/libXcursor.so.1.0.2
40fde000 40fe0000 r-xp /usr/lib/libXdamage.so.1.1.0
40fe9000 40feb000 r-xp /usr/lib/libXcomposite.so.1.0.0
40ff3000 40ff5000 r-xp /usr/lib/libXgesture.so.7.0.0
40ffd000 41000000 r-xp /usr/lib/libXfixes.so.3.1.0
41008000 41009000 r-xp /usr/lib/libXinerama.so.1.0.0
41012000 41018000 r-xp /usr/lib/libXrandr.so.2.2.0
41020000 41026000 r-xp /usr/lib/libXrender.so.1.3.0
4102f000 41033000 r-xp /usr/lib/libXtst.so.6.1.0
4103b000 41045000 r-xp /usr/lib/libXext.so.6.4.0
4104e000 41053000 r-xp /usr/lib/libecore_fb.so.1.7.99
4105c000 41060000 r-xp /usr/lib/libecore_ipc.so.1.7.99
41069000 4106c000 r-xp /usr/lib/libecore_input_evas.so.1.7.99
41075000 4108b000 r-xp /lib/libexpat.so.1.5.2
41095000 410ab000 r-xp /lib/libz.so.1.2.5
410b3000 410c5000 r-xp /usr/lib/libtts.so
410cd000 410ef000 r-xp /usr/lib/libui-extension.so.0.1.0
410f8000 410ff000 r-xp /usr/lib/libtbm.so.1.0.0
41108000 4110f000 r-xp /usr/lib/libembryo.so.1.7.99
41117000 4112e000 r-xp /usr/lib/liblua-5.1.so
41137000 41138000 r-xp /usr/lib/libecore_imf_evas.so.1.7.99
41140000 4114e000 r-xp /usr/lib/libGLESv2.so.2.0
41157000 4116f000 r-xp /usr/lib/libpng12.so.0.50.0
41178000 41179000 r-xp /usr/lib/libxcb-shm.so.0.0.0
41182000 41188000 r-xp /usr/lib/libxcb-render.so.0.0.0
41190000 411a3000 r-xp /usr/lib/libxcb.so.1.1.0
411ac000 411af000 r-xp /usr/lib/libEGL.so.1.4
411b7000 411da000 r-xp /usr/lib/libjpeg.so.8.0.2
411f3000 41237000 r-xp /usr/lib/libcurl.so.4.3.0
41240000 41258000 r-xp /usr/lib/liblzma.so.5.0.3
41260000 412dc000 r-xp /usr/lib/libgcrypt.so.20.0.3
412e8000 412f8000 r-xp /lib/libresolv-2.13.so
412fc000 412fe000 r-xp /usr/lib/libSLP-db-util.so.0.1.0
41308000 4130a000 r-xp /usr/lib/journal/libjournal.so.0.1.0
41312000 41313000 r-xp /usr/lib/libgthread-2.0.so.0.3200.3
4131b000 41320000 r-xp /usr/lib/libffi.so.5.0.10
41328000 4132a000 r-xp /usr/lib/libgmodule-2.0.so.0.3200.3
41333000 41338000 r-xp /usr/lib/libcapi-system-info.so.0.2.1
41340000 41343000 r-xp /usr/lib/libcapi-media-image-util.so.0.3.5
4134b000 4134c000 r-xp /usr/lib/libsecurity-privilege-checker.so.1.0.1
41355000 41492000 r-xp /usr/lib/libicui18n.so.51.1
414a2000 41586000 r-xp /usr/lib/libicuuc.so.51.1
4159c000 415a4000 r-xp /usr/lib/libdrm.so.2.4.0
415ac000 415ae000 r-xp /usr/lib/libdri2.so.0.0.0
415b6000 415b8000 r-xp /usr/lib/libXau.so.6.0.0
415c0000 415c9000 r-xp /usr/lib/libcares.so.2.1.0
415d2000 41600000 r-xp /usr/lib/libidn.so.11.5.44
41609000 41650000 r-xp /usr/lib/libssl.so.1.0.0
4165c000 41805000 r-xp /usr/lib/libcrypto.so.1.0.0
41826000 41831000 r-xp /usr/lib/libgpg-error.so.0.15.0
41839000 4183f000 r-xp /usr/lib/libmmutil_jpeg.so.0.0.0
41847000 4184c000 r-xp /usr/lib/libmmutil_imgp.so.0.0.0
41855000 41859000 r-xp /usr/lib/libsmack.so.1.0.0
41862000 4187b000 r-xp /usr/lib/libprivacy-manager-client.so.0.0.8
42e0d000 42e2e000 r-xp /usr/lib/libexif.so.12.3.3
42e41000 42e43000 r-xp /usr/lib/libttrace.so.1.1
42e4c000 42e51000 r-xp /usr/lib/libcapi-media-tool.so.0.1.5
42e59000 42e5f000 r-xp /usr/lib/libcapi-appfw-app-manager.so.0.2.8
42e68000 42e70000 r-xp /usr/lib/libcapi-appfw-package-manager.so.0.0.59
42e78000 42e94000 r-xp /usr/lib/libpkgmgr-client.so.0.1.68
42e9e000 42ea5000 r-xp /usr/lib/libpkgmgr_installer_client.so.0.1.0
42eae000 42eb0000 r-xp /usr/lib/libpkgmgr_installer_status_broadcast_server.so.0.1.0
42eb8000 42ee6000 r-xp /usr/lib/libsecurity-server-client.so.1.0.1
42eef000 42ef6000 r-xp /usr/lib/libminizip.so.1.0.0
42efe000 42f0b000 r-xp /usr/lib/libail.so.0.1.0
42f15000 42f32000 r-xp /usr/lib/libsecurity-server-commons.so.1.0.0
42f3b000 42f3d000 r-xp /usr/lib/libiri.so
42f45000 42f48000 r-xp /lib/libcap.so.2.21
42f50000 42f57000 r-xp /lib/libcrypt-2.13.so
42f87000 42f8a000 r-xp /lib/libattr.so.1.1.0
43098000 43162000 r-xp /usr/lib/libCOREGL.so.4.0
43174000 43198000 r-xp /usr/lib/ecore/immodules/libisf-imf-module.so
431a1000 43270000 r-xp /usr/lib/libscim-1.0.so.8.2.3
43286000 43290000 r-xp /lib/libnss_files-2.13.so
4349a000 43c99000 rw-p [stack:8692]
43c9a000 44499000 rw-p [stack:8693]
444af000 44cae000 rw-p [stack:8694]
44cae000 44cb9000 r-xp /usr/lib/evas/modules/engines/software_generic/linux-gnueabi-armv7l-1.7.99/module.so
44cc2000 44cc7000 r-xp /usr/lib/bufmgr/libtbm_exynos4412.so.0.0.0
44e01000 45600000 rw-p [stack:8705]
45600000 45677000 r-xp /usr/lib/evas/modules/engines/gl_x11/linux-gnueabi-armv7l-1.7.99/module.so
45687000 457cf000 r-xp /usr/lib/egl/libMali.so
457d5000 460d4000 rw-p [stack:8706]
befbb000 befdc000 rw-p [stack]
End of Maps Information

Callstack Information (PID:8683)
Call Stack Count: 1
 0: gsignal + 0x3c (0x403db9e8) [/lib/libc.so.6] + 0x2c9e8
End of Call Stack

Package Information
Package Name: org.example.sensorbasicui
Package ID : org.example.sensorbasicui
Version: 1.0.0
Package Type: rpm
App Name: sensorbasicui
App ID: org.example.sensorbasicui
Type: capp
Categories: 

Latest Debug Message Information
--------- beginning of /dev/log_main
tePort() Failed: MESSAGEPORT_ERROR_MESSAGEPORT_NOT_FOUND
10-24 19:05:56.481+0900 I/MESSAGE_PORT(  506): MessagePortIpcServer.cpp: Send(847) > _MessagePortIpcServer::Stop
10-24 19:05:56.486+0900 E/MESSAGE_PORT(  776): MessagePortProxy.cpp: CheckRemotePort(379) > The remote message port (music-control-service-request-message-port) is not found.
10-24 19:05:56.491+0900 W/W_HOME  (  776): clock_shortcut.c: _request_with_message_port(118) > remote port does not exist
10-24 19:05:56.491+0900 W/AUL     (  776): launch.c: app_request_to_launchpad(268) > request cmd(0) to(com.samsung.w-music-player.music-control-service)
10-24 19:05:56.491+0900 W/AUL_AMD (  540): amd_request.c: __request_handler(645) > __request_handler: 0
10-24 19:05:56.491+0900 E/AUL_AMD (  540): amd_request.c: __request_handler(669) > no appinfo
10-24 19:05:56.491+0900 E/AUL_AMD (  540): amd_appinfo.c: appinfo_get_value(1150) > appinfo get value: Invalid argument, 9
10-24 19:05:56.491+0900 E/PKGMGR_INFO(  540): pkgmgrinfo_pkginfo.c: pkgmgrinfo_updateinfo_check_update(2505) > (pkgid == NULL) pkgid is NULL
10-24 19:05:56.491+0900 E/AUL_AMD (  540): amd_appinfo.c: appinfo_get_value(1150) > appinfo get value: Invalid argument, 28
10-24 19:05:56.491+0900 E/AUL_AMD (  540): amd_appinfo.c: appinfo_get_value(1150) > appinfo get value: Invalid argument, 27
10-24 19:05:56.491+0900 W/AUL_AMD (  540): amd_launch.c: _start_app(1713) > caller pid : 776
10-24 19:05:56.491+0900 E/AUL_AMD (  540): amd_launch.c: _start_app(1726) > no appinfo
10-24 19:05:56.491+0900 E/AUL_AMD (  540): amd_launch.c: __real_send(835) > send fail to client
10-24 19:05:56.496+0900 W/AUL     (  776): launch.c: app_request_to_launchpad(282) > request cmd(0) result(-13)
10-24 19:05:56.496+0900 E/CAPI_APPFW_APP_CONTROL(  776): app_control.c: app_control_error(138) > [app_control_send_launch_request] APP_NOT_FOUND(0xfef00021)
10-24 19:05:56.496+0900 W/W_HOME  (  776): clock_shortcut.c: _mp_messageport_register(150) > err = fef00021
10-24 19:05:56.516+0900 I/APP_CORE( 8643): appcore-efl.c: __do_app(429) > [APP 8643] Event: RESUME State: RUNNING
10-24 19:05:56.516+0900 I/sensorbasicui( 8643): Calling the sensor update callback function:
10-24 19:05:56.521+0900 I/sensorbasicui( 8643): CREATED/OPENED TABLE DataTable
10-24 19:05:56.541+0900 W/wnotib  (  776): w-notification-board-broker-main.c: _wnb_ecore_x_event_visibility_changed_cb(420) > fully_obscured: 1
10-24 19:05:56.661+0900 W/CRASH_MANAGER( 8630): worker.c: worker_job(1205) > 060864373656e1571911556
10-24 19:05:56.826+0900 W/AUL_AMD (  540): amd_key.c: _key_ungrab(254) > fail(-1) to ungrab key(XF86Stop)
10-24 19:05:56.826+0900 W/AUL_AMD (  540): amd_launch.c: __e17_status_handler(2295) > back key ungrab error
10-24 19:05:56.851+0900 I/MALI    (  776): egl_platform_x11_tizen.c: tizen_update_native_surface_private(194) > [EGL-X11] surface->[0x442abba8] swap changed from sync to async
10-24 19:05:56.896+0900 W/PROCESSMGR(  419): e_mod_processmgr.c: _e_mod_processmgr_send_update_watch_action(639) > [PROCESSMGR] =====================> send UpdateClock
10-24 19:05:56.896+0900 W/W_HOME  (  776): event_manager.c: _ecore_x_message_cb(414) > state: 1 -> 0
10-24 19:05:56.896+0900 W/W_HOME  (  776): event_manager.c: _state_control(194) > control:4, app_state:2 win_state:0(0) pm_state:1 home_visible:0 clock_visible:1 tutorial_state:0 editing : 0, home_clocklist:0, addviewer:0 scrolling : 0, powersaving : 0, apptray state : 1, apptray visibility : 1, apptray edit visibility : 0
10-24 19:05:56.896+0900 W/W_HOME  (  776): event_manager.c: _state_control(194) > control:2, app_state:2 win_state:0(0) pm_state:1 home_visible:0 clock_visible:1 tutorial_state:0 editing : 0, home_clocklist:0, addviewer:0 scrolling : 0, powersaving : 0, apptray state : 1, apptray visibility : 1, apptray edit visibility : 0
10-24 19:05:56.911+0900 W/W_HOME  (  776): event_manager.c: _state_control(194) > control:1, app_state:2 win_state:0(0) pm_state:1 home_visible:0 clock_visible:1 tutorial_state:0 editing : 0, home_clocklist:0, addviewer:0 scrolling : 0, powersaving : 0, apptray state : 1, apptray visibility : 1, apptray edit visibility : 0
10-24 19:05:56.941+0900 W/W_HOME  (  776): event_manager.c: _window_visibility_cb(453) > Window [0x2800003] is now visible(0)
10-24 19:05:56.941+0900 W/W_HOME  (  776): event_manager.c: _window_visibility_cb(463) > state: 0 -> 1
10-24 19:05:56.941+0900 W/W_HOME  (  776): event_manager.c: _state_control(194) > control:4, app_state:2 win_state:0(1) pm_state:1 home_visible:0 clock_visible:1 tutorial_state:0 editing : 0, home_clocklist:0, addviewer:0 scrolling : 0, powersaving : 0, apptray state : 1, apptray visibility : 1, apptray edit visibility : 0
10-24 19:05:56.941+0900 W/W_HOME  (  776): main.c: _window_visibility_cb(1227) > Window [0x2800003] is now visible(0)
10-24 19:05:56.941+0900 I/APP_CORE(  776): appcore-efl.c: __do_app(429) > [APP 776] Event: RESUME State: PAUSED
10-24 19:05:56.941+0900 I/CAPI_APPFW_APPLICATION(  776): app_main.c: app_appcore_resume(223) > app_appcore_resume
10-24 19:05:56.941+0900 W/W_HOME  (  776): main.c: _appcore_resume_cb(685) > appcore resume
10-24 19:05:56.941+0900 W/W_HOME  (  776): event_manager.c: _app_resume_cb(366) > state: 2 -> 1
10-24 19:05:56.941+0900 W/W_HOME  (  776): event_manager.c: _state_control(194) > control:2, app_state:1 win_state:0(1) pm_state:1 home_visible:0 clock_visible:1 tutorial_state:0 editing : 0, home_clocklist:0, addviewer:0 scrolling : 0, powersaving : 0, apptray state : 1, apptray visibility : 1, apptray edit visibility : 0
10-24 19:05:56.946+0900 W/W_HOME  (  776): event_manager.c: _state_control(194) > control:0, app_state:1 win_state:0(1) pm_state:1 home_visible:0 clock_visible:1 tutorial_state:0 editing : 0, home_clocklist:0, addviewer:0 scrolling : 0, powersaving : 0, apptray state : 1, apptray visibility : 1, apptray edit visibility : 0
10-24 19:05:56.946+0900 W/W_HOME  (  776): event_manager.c: _state_control(194) > control:1, app_state:1 win_state:0(1) pm_state:1 home_visible:0 clock_visible:1 tutorial_state:0 editing : 0, home_clocklist:0, addviewer:0 scrolling : 0, powersaving : 0, apptray state : 1, apptray visibility : 1, apptray edit visibility : 0
10-24 19:05:56.946+0900 W/APPS    (  776): apps_main.c: _time_changed(303) >  date : 24->24
10-24 19:05:56.951+0900 W/wnotib  (  776): w-notification-board-broker-main.c: _wnb_ecore_x_event_visibility_changed_cb(420) > fully_obscured: 0
10-24 19:05:56.971+0900 W/WATCH_CORE(  818): appcore-watch.c: __signal_process_manager_handler(1190) > process_manager_signal
10-24 19:05:56.971+0900 I/WATCH_CORE(  818): appcore-watch.c: __signal_process_manager_handler(1206) > Call the time_tick_cb
10-24 19:05:56.971+0900 I/CAPI_WATCH_APPLICATION(  818): watch_app_main.c: _watch_core_time_tick(306) > _watch_core_time_tick
10-24 19:05:56.971+0900 E/watchface-loader(  818): watchface-loader.cpp: OnAppTimeTick(673) > 
10-24 19:05:56.971+0900 I/watchface-loader(  818): watchface-loader.cpp: OnAppTimeTick(684) > set force update!!
10-24 19:05:57.306+0900 W/AUL_PAD ( 1173): sigchild.h: __launchpad_process_sigchld(188) > dead_pid = 8643 pgid = 8643
10-24 19:05:57.311+0900 E/RESOURCED(  841): proc-stat.c: send_socket_with_repy(767) > send_socket_with_repy: read failed
10-24 19:05:57.311+0900 E/AUL     (  841): pkginfo.c: __get_id_bypid(212) > Failed to get the cmdline of pid, error: -1
10-24 19:05:57.311+0900 E/CAPI_APPFW_APP_MANAGER(  841): app_manager.c: app_manager_error(77) > [app_context_get_app_context_by_pid] No such application(0xfeef0001)
10-24 19:05:57.311+0900 E/RESOURCED( 7977): proc-stat.c: send_socket_with_repy(767) > send_socket_with_repy: read failed
10-24 19:05:57.311+0900 E/AUL     ( 7977): pkginfo.c: __get_id_bypid(212) > Failed to get the cmdline of pid, error: -1
10-24 19:05:57.311+0900 E/CAPI_APPFW_APP_MANAGER( 7977): app_manager.c: app_manager_error(77) > [app_context_get_app_context_by_pid] No such application(0xfeef0001)
10-24 19:05:57.321+0900 I/MALI    (  776): egl_platform_x11_tizen.c: tizen_update_native_surface_private(176) > [EGL-X11] surface->[0x442abba8] swap changed from async to sync
10-24 19:05:57.331+0900 E/RESOURCED(  542): resourced-dbus.c: resourced_dbus_system_hash_drop_busname(349) > Does not exist in busname hash: :1.1341
10-24 19:05:57.356+0900 E/RESOURCED( 1120): proc-stat.c: send_socket_with_repy(767) > send_socket_with_repy: read failed
10-24 19:05:57.356+0900 E/AUL     ( 1120): pkginfo.c: __get_id_bypid(212) > Failed to get the cmdline of pid, error: -1
10-24 19:05:57.356+0900 E/CAPI_APPFW_APP_MANAGER( 1120): app_manager.c: app_manager_error(77) > [app_context_get_app_context_by_pid] No such application(0xfeef0001)
10-24 19:05:57.371+0900 W/AUL_PAD ( 1173): sigchild.h: __launchpad_process_sigchld(196) > after __sigchild_action
10-24 19:05:57.376+0900 I/AUL_AMD (  540): amd_main.c: __app_dead_handler(263) > __app_dead_handler, pid: 8643
10-24 19:05:57.386+0900 E/RESOURCED(  542): resourced-dbus.c: resourced_dbus_system_hash_drop_busname(349) > Does not exist in busname hash: :1.1342
10-24 19:05:57.516+0900 E/EFL     ( 8680): elementary<8680> elm_main.c:558 elm_quicklaunch_init() eet_init done.
10-24 19:05:57.516+0900 E/EFL     ( 8680): elementary<8680> elm_main.c:560 elm_quicklaunch_init() ecore_init done.
10-24 19:05:57.641+0900 E/EFL     ( 8680): elementary<8680> elm_main.c:572 elm_quicklaunch_init() ecore_file_init done.
10-24 19:05:57.641+0900 E/EFL     ( 8680): elementary<8680> elm_main.c:595 elm_quicklaunch_init() _elm_screen_status_init done.
10-24 19:05:57.706+0900 E/EFL     ( 8680): elementary<8680> elm_main.c:625 elm_quicklaunch_init() e_dbus_init done.
10-24 19:05:57.706+0900 E/EFL     ( 8680): elementary<8680> elm_main.c:649 elm_quicklaunch_sub_init() evas_init done.
10-24 19:05:57.711+0900 E/EFL     ( 8680): elementary<8680> elm_main.c:651 elm_quicklaunch_sub_init() edje_init done.
10-24 19:05:57.711+0900 E/EFL     ( 8680): elementary<8680> elm_main.c:653 elm_quicklaunch_sub_init() _elm_module_init done.
10-24 19:05:57.711+0900 E/EFL     ( 8680): elementary<8680> elm_config.c:2747 _elm_config_init() _elm_config_init step 1 done.
10-24 19:05:57.731+0900 E/EFL     ( 8680): elementary<8680> elm_config.c:2755 _elm_config_init() _elm_config_init step 2 done.
10-24 19:05:57.751+0900 E/EFL     ( 8680): elementary<8680> elm_config.c:2759 _elm_config_init() _elm_config_init step 3 done.
10-24 19:05:57.896+0900 E/EFL     ( 8680): elementary<8680> elm_main.c:655 elm_quicklaunch_sub_init() _elm_config_init done.
10-24 19:05:57.936+0900 E/EFL     (  776): ecore_x<776> ecore_x_events.c:563 _ecore_x_event_handle_button_press() ButtonEvent:press time=75395603 button=1
10-24 19:05:57.941+0900 E/W_HOME  (  776): move.c: _mouse_move_cb(546) > apps move is not allowed
10-24 19:05:57.941+0900 E/W_HOME  (  776): move.c: _mouse_down_cb(384) > apps move is not allowed
10-24 19:05:57.941+0900 W/APPS    (  776): AppsViewList.cpp: _scrollerMouseDown(889) >  Find item [0,290,216,136]
10-24 19:05:57.956+0900 I/MESSAGE_PORT(  506): MessagePortIpcServer.cpp: OnReadMessage(739) > _MessagePortIpcServer::OnReadMessage
10-24 19:05:57.956+0900 I/MESSAGE_PORT(  506): MessagePortIpcServer.cpp: HandleReceivedMessage(578) > _MessagePortIpcServer::HandleReceivedMessage
10-24 19:05:57.956+0900 I/MESSAGE_PORT(  506): MessagePortStub.cpp: OnIpcRequestReceived(147) > MessagePort message received
10-24 19:05:57.956+0900 I/MESSAGE_PORT(  506): MessagePortStub.cpp: OnCheckRemotePort(115) > _MessagePortStub::OnCheckRemotePort.
10-24 19:05:57.956+0900 I/MESSAGE_PORT(  506): MessagePortService.cpp: CheckRemotePort(200) > _MessagePortService::CheckRemotePort
10-24 19:05:57.956+0900 I/MESSAGE_PORT(  506): MessagePortService.cpp: GetKey(358) > _MessagePortService::GetKey
10-24 19:05:57.956+0900 I/MESSAGE_PORT(  506): MessagePortService.cpp: CheckRemotePort(213) > Check a remote message port: [com.samsung.w-music-player.music-control-service:music-control-service-request-message-port]
10-24 19:05:57.956+0900 E/MESSAGE_PORT(  506): MessagePortService.cpp: CheckRemotePort(235) > _MessagePortService::CheckRemotePort() Failed: MESSAGEPORT_ERROR_MESSAGEPORT_NOT_FOUND
10-24 19:05:57.956+0900 I/MESSAGE_PORT(  506): MessagePortIpcServer.cpp: Send(847) > _MessagePortIpcServer::Stop
10-24 19:05:57.956+0900 E/MESSAGE_PORT(  776): MessagePortProxy.cpp: CheckRemotePort(379) > The remote message port (music-control-service-request-message-port) is not found.
10-24 19:05:57.956+0900 W/W_HOME  (  776): clock_shortcut.c: _request_with_message_port(118) > remote port does not exist
10-24 19:05:57.956+0900 W/AUL     (  776): launch.c: app_request_to_launchpad(268) > request cmd(0) to(com.samsung.w-music-player.music-control-service)
10-24 19:05:57.956+0900 W/AUL_AMD (  540): amd_request.c: __request_handler(645) > __request_handler: 0
10-24 19:05:57.956+0900 E/AUL_AMD (  540): amd_request.c: __request_handler(669) > no appinfo
10-24 19:05:57.961+0900 E/AUL_AMD (  540): amd_appinfo.c: appinfo_get_value(1150) > appinfo get value: Invalid argument, 9
10-24 19:05:57.961+0900 E/PKGMGR_INFO(  540): pkgmgrinfo_pkginfo.c: pkgmgrinfo_updateinfo_check_update(2505) > (pkgid == NULL) pkgid is NULL
10-24 19:05:57.961+0900 E/AUL_AMD (  540): amd_appinfo.c: appinfo_get_value(1150) > appinfo get value: Invalid argument, 28
10-24 19:05:57.961+0900 E/AUL_AMD (  540): amd_appinfo.c: appinfo_get_value(1150) > appinfo get value: Invalid argument, 27
10-24 19:05:57.961+0900 W/AUL_AMD (  540): amd_launch.c: _start_app(1713) > caller pid : 776
10-24 19:05:57.961+0900 E/AUL_AMD (  540): amd_launch.c: _start_app(1726) > no appinfo
10-24 19:05:57.961+0900 E/AUL_AMD (  540): amd_launch.c: __real_send(835) > send fail to client
10-24 19:05:57.961+0900 W/AUL     (  776): launch.c: app_request_to_launchpad(282) > request cmd(0) result(-13)
10-24 19:05:57.961+0900 E/CAPI_APPFW_APP_CONTROL(  776): app_control.c: app_control_error(138) > [app_control_send_launch_request] APP_NOT_FOUND(0xfef00021)
10-24 19:05:57.961+0900 W/W_HOME  (  776): clock_shortcut.c: _mp_messageport_register(150) > err = fef00021
10-24 19:05:58.011+0900 E/EFL     (  776): ecore_x<776> ecore_x_events.c:722 _ecore_x_event_handle_button_release() ButtonEvent:release time=75395676 button=1
10-24 19:05:58.011+0900 W/APPS    (  776): AppsItem.cpp: onItemClicked(444) >  onItemClicked[0,12]
10-24 19:05:58.011+0900 E/APPS    (  776): effect.c: apps_effect_play_sound(86) >  effect_info.sound_status: [0]
10-24 19:05:58.011+0900 W/APPS    (  776): AppsItem.cpp: onItemClicked(456) >  item(sensorbasicui) launched, open(0)
10-24 19:05:58.021+0900 W/AUL     (  776): launch.c: app_request_to_launchpad(268) > request cmd(0) to(org.example.sensorbasicui)
10-24 19:05:58.021+0900 W/AUL_AMD (  540): amd_request.c: __request_handler(645) > __request_handler: 0
10-24 19:05:58.021+0900 W/AUL_AMD (  540): amd_launch.c: _start_app(1713) > caller pid : 776
10-24 19:05:58.021+0900 I/AUL_AMD (  540): amd_launch.c: __check_app_control_privilege(1602) > Skip the privilege check in case of preloaded apps
10-24 19:05:58.031+0900 E/RESOURCED(  542): block.c: block_prelaunch_state(134) > insert data org.example.sensorbasicui, table num : 1
10-24 19:05:58.031+0900 E/RESOURCED(  542): heart-memory.c: heart_memory_get_data(601) > hashtable heart_memory_app_list is NULL
10-24 19:05:58.036+0900 W/AUL_AMD (  540): amd_launch.c: _start_app(2127) > pad pid(-5)
10-24 19:05:58.036+0900 W/AUL_PAD ( 1173): launchpad.c: __launchpad_main_loop(620) > Candidate is not prepared, enter legacy logic
10-24 19:05:58.036+0900 W/AUL_PAD ( 1173): launchpad.c: __send_result_to_caller(272) > Check app launching
10-24 19:05:58.036+0900 E/AUL_PAD ( 1173): launchpad.c: __send_result_to_caller(278) > launching failed
10-24 19:05:58.036+0900 W/AUL_AMD (  540): amd_launch.c: _start_app(2138) > Launch with legacy way : no launchpad
10-24 19:05:58.041+0900 W/AUL_AMD (  540): amd_launch.c: start_process(581) > child process: 8683
10-24 19:05:58.091+0900 W/AUL_AMD (  540): amd_launch.c: __send_app_launch_signal(380) > send launch signal done: 8683
10-24 19:05:58.091+0900 E/AUL     (  540): app_signal.c: __app_dbus_signal_filter(94) > reject by security issue - no interface
10-24 19:05:58.091+0900 W/AUL     (  776): launch.c: app_request_to_launchpad(282) > request cmd(0) result(8683)
10-24 19:05:58.101+0900 E/RESOURCED(  542): proc-main.c: proc_add_program_list(233) > not found ppi : org.example.sensorbasicui
10-24 19:05:58.111+0900 W/AUL_AMD (  540): amd_request.c: __request_handler(645) > __request_handler: 14
10-24 19:05:58.116+0900 W/AUL_AMD (  540): amd_request.c: __send_result_to_client(83) > __send_result_to_client, pid: 8683
10-24 19:05:58.121+0900 W/AUL_AMD (  540): amd_request.c: __request_handler(645) > __request_handler: 12
10-24 19:05:58.316+0900 I/efl-extension( 8683): efl_extension.c: eext_mod_init(40) > Init
10-24 19:05:58.351+0900 I/CAPI_APPFW_APPLICATION( 8683): app_main.c: ui_app_main(704) > app_efl_main
10-24 19:05:58.386+0900 E/EFL     ( 8683): elementary<8683> elm_main.c:558 elm_quicklaunch_init() eet_init done.
10-24 19:05:58.396+0900 E/EFL     ( 8683): elementary<8683> elm_main.c:560 elm_quicklaunch_init() ecore_init done.
10-24 19:05:58.421+0900 E/EFL     ( 8683): elementary<8683> elm_main.c:572 elm_quicklaunch_init() ecore_file_init done.
10-24 19:05:58.426+0900 I/UXT     ( 8683): Uxt_ObjectManager.cpp: OnInitialized(735) > Initialized.
10-24 19:05:58.426+0900 E/EFL     ( 8683): elementary<8683> elm_main.c:595 elm_quicklaunch_init() _elm_screen_status_init done.
10-24 19:05:58.461+0900 E/EFL     ( 8683): elementary<8683> elm_main.c:625 elm_quicklaunch_init() e_dbus_init done.
10-24 19:05:58.461+0900 E/EFL     ( 8683): elementary<8683> elm_main.c:649 elm_quicklaunch_sub_init() evas_init done.
10-24 19:05:58.461+0900 E/EFL     ( 8683): elementary<8683> elm_main.c:651 elm_quicklaunch_sub_init() edje_init done.
10-24 19:05:58.461+0900 E/EFL     ( 8683): elementary<8683> elm_main.c:653 elm_quicklaunch_sub_init() _elm_module_init done.
10-24 19:05:58.461+0900 E/EFL     ( 8683): elementary<8683> elm_config.c:2747 _elm_config_init() _elm_config_init step 1 done.
10-24 19:05:58.481+0900 E/EFL     ( 8683): elementary<8683> elm_config.c:2755 _elm_config_init() _elm_config_init step 2 done.
10-24 19:05:58.481+0900 E/EFL     ( 8683): elementary<8683> elm_config.c:2759 _elm_config_init() _elm_config_init step 3 done.
10-24 19:05:58.486+0900 E/EFL     ( 8683): elementary<8683> elm_main.c:655 elm_quicklaunch_sub_init() _elm_config_init done.
10-24 19:05:58.511+0900 E/EFL     ( 8683): elementary<8683> elm_config.c:2799 _elm_config_sub_init() ecore_x_init done.
10-24 19:05:58.521+0900 E/EFL     ( 8683): elementary<8683> elm_config.c:2854 _elm_config_sub_init() _config_sub_apply done.
10-24 19:05:58.521+0900 E/EFL     ( 8683): elementary<8683> elm_main.c:657 elm_quicklaunch_sub_init() _elm_config_sub_init done.
10-24 19:05:58.521+0900 E/EFL     ( 8683): elementary<8683> elm_main.c:659 elm_quicklaunch_sub_init() ecore_evas_init done.
10-24 19:05:58.521+0900 E/EFL     ( 8683): elementary<8683> elm_main.c:666 elm_quicklaunch_sub_init() ecore_con_init done.
10-24 19:05:58.521+0900 E/EFL     ( 8683): elementary<8683> elm_main.c:668 elm_quicklaunch_sub_init() ecore_con_url_init done.
10-24 19:05:58.521+0900 E/EFL     ( 8683): elementary<8683> elm_main.c:671 elm_quicklaunch_sub_init() _elm_ews_wm_init done.
10-24 19:05:58.571+0900 I/CAPI_APPFW_APPLICATION( 8683): app_main.c: _ui_app_appcore_create(563) > app_appcore_create
10-24 19:05:58.621+0900 E/sensorbasicui( 8683): [../src/data.c:219] sensor_get_default_sensor() error MAGNETIC: Not supported
10-24 19:05:58.621+0900 E/sensorbasicui( 8683): [../src/data.c:219] sensor_get_default_sensor() error ROTATION VECTOR: Not supported
10-24 19:05:58.621+0900 E/sensorbasicui( 8683): [../src/data.c:219] sensor_get_default_sensor() error ORIENTATION: Not supported
10-24 19:05:58.626+0900 E/sensorbasicui( 8683): [../src/data.c:219] sensor_get_default_sensor() error LIGHT: Not supported
10-24 19:05:58.626+0900 E/sensorbasicui( 8683): [../src/data.c:219] sensor_get_default_sensor() error PROXIMITY: Not supported
10-24 19:05:58.626+0900 E/sensorbasicui( 8683): [../src/data.c:219] sensor_get_default_sensor() error ULTRAVIOLET: Not supported
10-24 19:05:58.626+0900 E/sensorbasicui( 8683): [../src/data.c:219] sensor_get_default_sensor() error TEMPERATURE: Not supported
10-24 19:05:58.626+0900 E/sensorbasicui( 8683): [../src/data.c:219] sensor_get_default_sensor() error HUMIDITY: Not supported
10-24 19:05:58.631+0900 I/sensorbasicui( 8683): Set activity of sensor: HRM to 1
10-24 19:05:58.631+0900 E/sensorbasicui( 8683): Initialized data
10-24 19:05:58.681+0900 I/sensorbasicui( 8683): OPENED DATABASE /opt/usr/apps/org.example.sensorbasicui/data/test.db SUCCESFULLY
10-24 19:05:58.681+0900 I/sensorbasicui( 8683): Started making the GUI, app has launched
10-24 19:05:58.866+0900 E/EFL     ( 8683): ecore_evas<8683> ecore_evas_extn.c:2202 ecore_evas_extn_plug_connect() Extn plug failed to connect:ipctype=0, svcname=elm_indicator_portrait, svcnum=0, svcsys=0
10-24 19:05:58.866+0900 W/AUL_AMD (  540): amd_request.c: __request_handler(645) > __request_handler: 14
10-24 19:05:58.871+0900 W/AUL_AMD (  540): amd_request.c: __send_result_to_client(83) > __send_result_to_client, pid: 8683
10-24 19:05:58.871+0900 E/EFL     (  540): ecore_x<540> ecore_x_events.c:563 _ecore_x_event_handle_button_press() ButtonEvent:press time=75396395 button=1
10-24 19:05:58.871+0900 E/EFL     (  540): ecore_x<540> ecore_x_events.c:722 _ecore_x_event_handle_button_release() ButtonEvent:release time=75396443 button=1
10-24 19:05:58.871+0900 W/AUL_AMD (  540): amd_status.c: __socket_monitor_cb(1292) > (8683) was created
10-24 19:05:58.991+0900 W/W_HOME  (  776): event_manager.c: _ecore_x_message_cb(414) > state: 0 -> 1
10-24 19:05:58.991+0900 W/W_HOME  (  776): event_manager.c: _state_control(194) > control:4, app_state:1 win_state:1(1) pm_state:1 home_visible:0 clock_visible:1 tutorial_state:0 editing : 0, home_clocklist:0, addviewer:0 scrolling : 0, powersaving : 0, apptray state : 0, apptray visibility : 1, apptray edit visibility : 0
10-24 19:05:58.991+0900 W/W_HOME  (  776): event_manager.c: _state_control(194) > control:2, app_state:1 win_state:1(1) pm_state:1 home_visible:0 clock_visible:1 tutorial_state:0 editing : 0, home_clocklist:0, addviewer:0 scrolling : 0, powersaving : 0, apptray state : 0, apptray visibility : 1, apptray edit visibility : 0
10-24 19:05:58.991+0900 W/W_HOME  (  776): event_manager.c: _state_control(194) > control:1, app_state:1 win_state:1(1) pm_state:1 home_visible:0 clock_visible:1 tutorial_state:0 editing : 0, home_clocklist:0, addviewer:0 scrolling : 0, powersaving : 0, apptray state : 0, apptray visibility : 1, apptray edit visibility : 0
10-24 19:05:58.996+0900 W/AUL_AMD (  540): amd_request.c: __request_handler(645) > __request_handler: 12
10-24 19:05:58.996+0900 W/AUL_AMD (  540): amd_request.c: __request_handler(645) > __request_handler: 14
10-24 19:05:59.006+0900 W/AUL_AMD (  540): amd_request.c: __send_result_to_client(83) > __send_result_to_client, pid: 8683
10-24 19:05:59.026+0900 I/APP_CORE( 8683): appcore-efl.c: __do_app(429) > [APP 8683] Event: RESET State: CREATED
10-24 19:05:59.026+0900 I/CAPI_APPFW_APPLICATION( 8683): app_main.c: _ui_app_appcore_reset(645) > app_appcore_reset
10-24 19:05:59.031+0900 W/AUL_AMD (  540): amd_request.c: __request_handler(645) > __request_handler: 12
10-24 19:05:59.061+0900 I/APP_CORE( 8683): appcore-efl.c: __do_app(472) > Legacy lifecycle: 0
10-24 19:05:59.061+0900 I/APP_CORE( 8683): appcore-efl.c: __do_app(474) > [APP 8683] Initial Launching, call the resume_cb
10-24 19:05:59.061+0900 I/CAPI_APPFW_APPLICATION( 8683): app_main.c: _ui_app_appcore_resume(628) > app_appcore_resume
10-24 19:05:59.076+0900 W/APP_CORE( 8683): appcore-efl.c: __show_cb(787) > [EVENT_TEST][EVENT] GET SHOW EVENT!!!. WIN:5600003
10-24 19:05:59.096+0900 I/MALI    ( 8683): egl_platform_x11_tizen.c: _tizen_platform_acquire_buffer(742) > [EGL-X11] surface has been resized, clean up all the render target [1x1] -> [216x432]
10-24 19:05:59.116+0900 W/W_HOME  (  776): event_manager.c: _window_visibility_cb(453) > Window [0x2800003] is now visible(1)
10-24 19:05:59.116+0900 W/W_HOME  (  776): event_manager.c: _window_visibility_cb(463) > state: 1 -> 0
10-24 19:05:59.116+0900 W/W_HOME  (  776): event_manager.c: _state_control(194) > control:4, app_state:1 win_state:1(0) pm_state:1 home_visible:0 clock_visible:1 tutorial_state:0 editing : 0, home_clocklist:0, addviewer:0 scrolling : 0, powersaving : 0, apptray state : 0, apptray visibility : 1, apptray edit visibility : 0
10-24 19:05:59.116+0900 W/W_HOME  (  776): main.c: _window_visibility_cb(1227) > Window [0x2800003] is now visible(1)
10-24 19:05:59.121+0900 I/APP_CORE(  776): appcore-efl.c: __do_app(429) > [APP 776] Event: PAUSE State: RUNNING
10-24 19:05:59.121+0900 I/CAPI_APPFW_APPLICATION(  776): app_main.c: app_appcore_pause(202) > app_appcore_pause
10-24 19:05:59.121+0900 W/W_HOME  (  776): main.c: _appcore_pause_cb(694) > appcore pause
10-24 19:05:59.121+0900 W/W_HOME  (  776): event_manager.c: _app_pause_cb(383) > state: 1 -> 2
10-24 19:05:59.121+0900 W/W_HOME  (  776): event_manager.c: _state_control(194) > control:2, app_state:2 win_state:1(0) pm_state:1 home_visible:0 clock_visible:1 tutorial_state:0 editing : 0, home_clocklist:0, addviewer:0 scrolling : 0, powersaving : 0, apptray state : 0, apptray visibility : 1, apptray edit visibility : 0
10-24 19:05:59.121+0900 W/W_HOME  (  776): event_manager.c: _state_control(194) > control:0, app_state:2 win_state:1(0) pm_state:1 home_visible:0 clock_visible:1 tutorial_state:0 editing : 0, home_clocklist:0, addviewer:0 scrolling : 0, powersaving : 0, apptray state : 0, apptray visibility : 1, apptray edit visibility : 0
10-24 19:05:59.121+0900 W/W_HOME  (  776): event_manager.c: _state_control(194) > control:1, app_state:2 win_state:1(0) pm_state:1 home_visible:0 clock_visible:1 tutorial_state:0 editing : 0, home_clocklist:0, addviewer:0 scrolling : 0, powersaving : 0, apptray state : 0, apptray visibility : 1, apptray edit visibility : 0
10-24 19:05:59.121+0900 I/MESSAGE_PORT(  506): MessagePortIpcServer.cpp: OnReadMessage(739) > _MessagePortIpcServer::OnReadMessage
10-24 19:05:59.121+0900 I/MESSAGE_PORT(  506): MessagePortIpcServer.cpp: HandleReceivedMessage(578) > _MessagePortIpcServer::HandleReceivedMessage
10-24 19:05:59.121+0900 I/MESSAGE_PORT(  506): MessagePortStub.cpp: OnIpcRequestReceived(147) > MessagePort message received
10-24 19:05:59.121+0900 I/MESSAGE_PORT(  506): MessagePortStub.cpp: OnCheckRemotePort(115) > _MessagePortStub::OnCheckRemotePort.
10-24 19:05:59.121+0900 I/MESSAGE_PORT(  506): MessagePortService.cpp: CheckRemotePort(200) > _MessagePortService::CheckRemotePort
10-24 19:05:59.121+0900 I/MESSAGE_PORT(  506): MessagePortService.cpp: GetKey(358) > _MessagePortService::GetKey
10-24 19:05:59.121+0900 I/MESSAGE_PORT(  506): MessagePortService.cpp: CheckRemotePort(213) > Check a remote message port: [com.samsung.w-music-player.music-control-service:music-control-service-request-message-port]
10-24 19:05:59.121+0900 E/MESSAGE_PORT(  506): MessagePortService.cpp: CheckRemotePort(235) > _MessagePortService::CheckRemotePort() Failed: MESSAGEPORT_ERROR_MESSAGEPORT_NOT_FOUND
10-24 19:05:59.121+0900 I/MESSAGE_PORT(  506): MessagePortIpcServer.cpp: Send(847) > _MessagePortIpcServer::Stop
10-24 19:05:59.126+0900 E/MESSAGE_PORT(  776): MessagePortProxy.cpp: CheckRemotePort(379) > The remote message port (music-control-service-request-message-port) is not found.
10-24 19:05:59.126+0900 W/W_HOME  (  776): clock_shortcut.c: _request_with_message_port(118) > remote port does not exist
10-24 19:05:59.126+0900 W/AUL     (  776): launch.c: app_request_to_launchpad(268) > request cmd(0) to(com.samsung.w-music-player.music-control-service)
10-24 19:05:59.126+0900 W/AUL_AMD (  540): amd_request.c: __request_handler(645) > __request_handler: 0
10-24 19:05:59.126+0900 E/AUL_AMD (  540): amd_request.c: __request_handler(669) > no appinfo
10-24 19:05:59.126+0900 E/AUL_AMD (  540): amd_appinfo.c: appinfo_get_value(1150) > appinfo get value: Invalid argument, 9
10-24 19:05:59.126+0900 E/PKGMGR_INFO(  540): pkgmgrinfo_pkginfo.c: pkgmgrinfo_updateinfo_check_update(2505) > (pkgid == NULL) pkgid is NULL
10-24 19:05:59.126+0900 E/AUL_AMD (  540): amd_appinfo.c: appinfo_get_value(1150) > appinfo get value: Invalid argument, 28
10-24 19:05:59.126+0900 E/AUL_AMD (  540): amd_appinfo.c: appinfo_get_value(1150) > appinfo get value: Invalid argument, 27
10-24 19:05:59.126+0900 W/AUL_AMD (  540): amd_launch.c: _start_app(1713) > caller pid : 776
10-24 19:05:59.126+0900 E/AUL_AMD (  540): amd_launch.c: _start_app(1726) > no appinfo
10-24 19:05:59.126+0900 E/AUL_AMD (  540): amd_launch.c: __real_send(835) > send fail to client
10-24 19:05:59.126+0900 W/AUL     (  776): launch.c: app_request_to_launchpad(282) > request cmd(0) result(-13)
10-24 19:05:59.126+0900 E/CAPI_APPFW_APP_CONTROL(  776): app_control.c: app_control_error(138) > [app_control_send_launch_request] APP_NOT_FOUND(0xfef00021)
10-24 19:05:59.126+0900 W/W_HOME  (  776): clock_shortcut.c: _mp_messageport_register(150) > err = fef00021
10-24 19:05:59.141+0900 W/AUL_AMD (  540): amd_key.c: _key_ungrab(254) > fail(-1) to ungrab key(XF86Stop)
10-24 19:05:59.141+0900 W/AUL_AMD (  540): amd_launch.c: __e17_status_handler(2295) > back key ungrab error
10-24 19:05:59.151+0900 E/TBM     (  419): tbm_bufmgr.c: _tgl_destroy(151) > [libtbm:419] error(Device or resource busy) _tgl_destroy:151 key:33
10-24 19:05:59.156+0900 I/APP_CORE( 8683): appcore-efl.c: __do_app(429) > [APP 8683] Event: RESUME State: RUNNING
10-24 19:05:59.161+0900 I/sensorbasicui( 8683): Calling the sensor update callback function:
10-24 19:05:59.166+0900 I/sensorbasicui( 8683): CREATED/OPENED TABLE DataTable
10-24 19:05:59.241+0900 W/wnotib  (  776): w-notification-board-broker-main.c: _wnb_ecore_x_event_visibility_changed_cb(420) > fully_obscured: 1
10-24 19:05:59.466+0900 E/AUL     (  540): app_signal.c: __app_dbus_signal_filter(94) > reject by security issue - no interface
10-24 19:05:59.636+0900 I/APP_CORE(  776): appcore-efl.c: __do_app(429) > [APP 776] Event: MEM_FLUSH State: PAUSED
10-24 19:05:59.711+0900 W/AUL     ( 8710): daemon-manager-release-agent.c: main(12) > release agent : [2:/org.example.sensorbasicui]
10-24 19:05:59.721+0900 W/AUL_AMD (  540): amd_request.c: __request_handler(645) > __request_handler: 23
10-24 19:05:59.721+0900 W/AUL_AMD (  540): amd_request.c: __send_result_to_client(83) > __send_result_to_client, pid: 0
10-24 19:05:59.721+0900 W/AUL_AMD (  540): amd_request.c: __request_handler(949) > pkg_status: installed, dead pid: 8683
10-24 19:05:59.721+0900 W/AUL_AMD (  540): amd_request.c: __send_app_termination_signal(510) > send dead signal done
10-24 19:05:59.746+0900 I/MALI    (  776): egl_platform_x11_tizen.c: tizen_update_native_surface_private(194) > [EGL-X11] surface->[0x442abba8] swap changed from sync to async
10-24 19:05:59.811+0900 W/AUL_AMD (  540): amd_key.c: _key_ungrab(254) > fail(-1) to ungrab key(XF86Stop)
10-24 19:05:59.811+0900 W/AUL_AMD (  540): amd_launch.c: __e17_status_handler(2295) > back key ungrab error
10-24 19:05:59.821+0900 W/PROCESSMGR(  419): e_mod_processmgr.c: _e_mod_processmgr_send_update_watch_action(639) > [PROCESSMGR] =====================> send UpdateClock
10-24 19:05:59.821+0900 W/W_HOME  (  776): event_manager.c: _ecore_x_message_cb(414) > state: 1 -> 0
10-24 19:05:59.821+0900 W/W_HOME  (  776): event_manager.c: _state_control(194) > control:4, app_state:2 win_state:0(0) pm_state:1 home_visible:0 clock_visible:1 tutorial_state:0 editing : 0, home_clocklist:0, addviewer:0 scrolling : 0, powersaving : 0, apptray state : 1, apptray visibility : 1, apptray edit visibility : 0
10-24 19:05:59.821+0900 W/W_HOME  (  776): event_manager.c: _state_control(194) > control:2, app_state:2 win_state:0(0) pm_state:1 home_visible:0 clock_visible:1 tutorial_state:0 editing : 0, home_clocklist:0, addviewer:0 scrolling : 0, powersaving : 0, apptray state : 1, apptray visibility : 1, apptray edit visibility : 0
10-24 19:05:59.826+0900 W/W_HOME  (  776): event_manager.c: _state_control(194) > control:1, app_state:2 win_state:0(0) pm_state:1 home_visible:0 clock_visible:1 tutorial_state:0 editing : 0, home_clocklist:0, addviewer:0 scrolling : 0, powersaving : 0, apptray state : 1, apptray visibility : 1, apptray edit visibility : 0
10-24 19:05:59.836+0900 I/AUL_AMD (  540): amd_main.c: __app_dead_handler(263) > __app_dead_handler, pid: 8683
10-24 19:05:59.841+0900 W/WATCH_CORE(  818): appcore-watch.c: __signal_process_manager_handler(1190) > process_manager_signal
10-24 19:05:59.841+0900 I/WATCH_CORE(  818): appcore-watch.c: __signal_process_manager_handler(1206) > Call the time_tick_cb
10-24 19:05:59.841+0900 I/CAPI_WATCH_APPLICATION(  818): watch_app_main.c: _watch_core_time_tick(306) > _watch_core_time_tick
10-24 19:05:59.841+0900 E/watchface-loader(  818): watchface-loader.cpp: OnAppTimeTick(673) > 
10-24 19:05:59.841+0900 I/watchface-loader(  818): watchface-loader.cpp: OnAppTimeTick(684) > set force update!!
10-24 19:05:59.876+0900 W/W_HOME  (  776): event_manager.c: _window_visibility_cb(453) > Window [0x2800003] is now visible(0)
10-24 19:05:59.881+0900 W/W_HOME  (  776): event_manager.c: _window_visibility_cb(463) > state: 0 -> 1
10-24 19:05:59.881+0900 W/W_HOME  (  776): event_manager.c: _state_control(194) > control:4, app_state:2 win_state:0(1) pm_state:1 home_visible:0 clock_visible:1 tutorial_state:0 editing : 0, home_clocklist:0, addviewer:0 scrolling : 0, powersaving : 0, apptray state : 1, apptray visibility : 1, apptray edit visibility : 0
10-24 19:05:59.881+0900 W/W_HOME  (  776): main.c: _window_visibility_cb(1227) > Window [0x2800003] is now visible(0)
10-24 19:05:59.881+0900 I/APP_CORE(  776): appcore-efl.c: __do_app(429) > [APP 776] Event: RESUME State: PAUSED
10-24 19:05:59.881+0900 I/CAPI_APPFW_APPLICATION(  776): app_main.c: app_appcore_resume(223) > app_appcore_resume
10-24 19:05:59.881+0900 W/W_HOME  (  776): main.c: _appcore_resume_cb(685) > appcore resume
10-24 19:05:59.881+0900 W/W_HOME  (  776): event_manager.c: _app_resume_cb(366) > state: 2 -> 1
10-24 19:05:59.881+0900 W/W_HOME  (  776): event_manager.c: _state_control(194) > control:2, app_state:1 win_state:0(1) pm_state:1 home_visible:0 clock_visible:1 tutorial_state:0 editing : 0, home_clocklist:0, addviewer:0 scrolling : 0, powersaving : 0, apptray state : 1, apptray visibility : 1, apptray edit visibility : 0
10-24 19:05:59.886+0900 W/W_HOME  (  776): event_manager.c: _state_control(194) > control:0, app_state:1 win_state:0(1) pm_state:1 home_visible:0 clock_visible:1 tutorial_state:0 editing : 0, home_clocklist:0, addviewer:0 scrolling : 0, powersaving : 0, apptray state : 1, apptray visibility : 1, apptray edit visibility : 0
10-24 19:05:59.886+0900 W/W_HOME  (  776): event_manager.c: _state_control(194) > control:1, app_state:1 win_state:0(1) pm_state:1 home_visible:0 clock_visible:1 tutorial_state:0 editing : 0, home_clocklist:0, addviewer:0 scrolling : 0, powersaving : 0, apptray state : 1, apptray visibility : 1, apptray edit visibility : 0
10-24 19:05:59.886+0900 W/APPS    (  776): apps_main.c: _time_changed(303) >  date : 24->24
10-24 19:05:59.901+0900 W/wnotib  (  776): w-notification-board-broker-main.c: _wnb_ecore_x_event_visibility_changed_cb(420) > fully_obscured: 0
10-24 19:06:00.261+0900 I/MALI    (  776): egl_platform_x11_tizen.c: tizen_update_native_surface_private(176) > [EGL-X11] surface->[0x442abba8] swap changed from async to sync
10-24 19:06:00.316+0900 E/WMS     (  537): wms_event_handler.c: _wms_event_handler_cb_nomove_detector(23255) > _wms_event_handler_cb_nomove_detector is called
10-24 19:06:00.396+0900 E/EFL     ( 8680): elementary<8680> elm_config.c:2799 _elm_config_sub_init() ecore_x_init done.
10-24 19:06:00.416+0900 E/EFL     ( 8680): elementary<8680> elm_config.c:2854 _elm_config_sub_init() _config_sub_apply done.
10-24 19:06:00.416+0900 E/EFL     ( 8680): elementary<8680> elm_main.c:657 elm_quicklaunch_sub_init() _elm_config_sub_init done.
10-24 19:06:00.416+0900 E/EFL     ( 8680): elementary<8680> elm_main.c:659 elm_quicklaunch_sub_init() ecore_evas_init done.
10-24 19:06:00.421+0900 E/EFL     ( 8680): elementary<8680> elm_main.c:666 elm_quicklaunch_sub_init() ecore_con_init done.
10-24 19:06:00.421+0900 E/EFL     ( 8680): elementary<8680> elm_main.c:668 elm_quicklaunch_sub_init() ecore_con_url_init done.
10-24 19:06:00.421+0900 E/EFL     ( 8680): elementary<8680> elm_main.c:671 elm_quicklaunch_sub_init() _elm_ews_wm_init done.
10-24 19:06:00.421+0900 I/AUL_PAD ( 8680): launchpad_loader.c: main(580) > [candidate] elm init, returned: 1
10-24 19:06:00.481+0900 W/WATCH_CORE(  818): appcore-watch.c: __signal_context_handler(1219) > _signal_context_handler: type: 0, state: 3
10-24 19:06:00.481+0900 I/WATCH_CORE(  818): appcore-watch.c: __signal_context_handler(1236) > Call the time_tick_cb
10-24 19:06:00.481+0900 I/CAPI_WATCH_APPLICATION(  818): watch_app_main.c: _watch_core_time_tick(306) > _watch_core_time_tick
10-24 19:06:00.481+0900 E/watchface-loader(  818): watchface-loader.cpp: OnAppTimeTick(673) > 
10-24 19:06:00.481+0900 I/watchface-loader(  818): watchface-loader.cpp: OnAppTimeTick(684) > set force update!!
10-24 19:06:00.481+0900 E/BASE_UTILS(  818): utils_i18n_udate.c: i18n_udate_format_date(52) > err(-22020089): A result would not fit in the supplied buffer
10-24 19:06:00.481+0900 I/watchface-viewer(  818): viewer-part-resource-evas.cpp: CreateTextImage(866) > style[DEFAULT='font=Default font_size=40 color=#FFFFFF ellipsis=-1 align=left ']
10-24 19:06:00.481+0900 I/watchface-viewer(  818): viewer-part-resource-evas.cpp: CreateTextImage(880) > formatted size 86x109
10-24 19:06:00.496+0900 E/BASE_UTILS(  818): utils_i18n_udate.c: i18n_udate_format_date(52) > err(-22020089): A result would not fit in the supplied buffer
10-24 19:06:00.501+0900 I/watchface-viewer(  818): viewer-part-resource-evas.cpp: CreateTextImage(866) > style[DEFAULT='font=Default font_size=40 color=#FFFFFF ellipsis=-1 align=left ']
10-24 19:06:00.501+0900 I/watchface-viewer(  818): viewer-part-resource-evas.cpp: CreateTextImage(880) > formatted size 86x109
10-24 19:06:00.506+0900 I/watchface-viewer(  818): viewer-image-file-loader.cpp: OnImageLoadingDoneIdlerCb(565) > ImagesLoadingDoneSignal().Emit()
10-24 19:06:00.526+0900 W/WATCH_CORE(  818): appcore-watch.c: __signal_lcd_status_handler(1157) > signal_lcd_status_signal: LCDOff
10-24 19:06:00.526+0900 W/W_HOME  (  776): dbus.c: _dbus_message_recv_cb(204) > LCD off
10-24 19:06:00.526+0900 W/W_HOME  (  776): gesture.c: _manual_render_cancel_schedule(229) > cancel schedule, manual render
10-24 19:06:00.526+0900 W/W_HOME  (  776): gesture.c: _manual_render_disable_timer_del(155) > timer del
10-24 19:06:00.526+0900 W/W_HOME  (  776): gesture.c: _manual_render_enable(136) > 1
10-24 19:06:00.526+0900 W/W_HOME  (  776): event_manager.c: _lcd_off_cb(704) > lcd state: 0
10-24 19:06:00.526+0900 W/W_HOME  (  776): event_manager.c: _state_control(194) > control:4, app_state:1 win_state:0(1) pm_state:0 home_visible:0 clock_visible:1 tutorial_state:0 editing : 0, home_clocklist:0, addviewer:0 scrolling : 0, powersaving : 0, apptray state : 0, apptray visibility : 1, apptray edit visibility : 0
10-24 19:06:00.531+0900 W/STARTER (  741): clock-mgr.c: _on_lcd_signal_receive_cb(1648) > [_on_lcd_signal_receive_cb:1648] _on_lcd_signal_receive_cb, 1648, Pre LCD off by [gesture]
10-24 19:06:00.531+0900 W/STARTER (  741): clock-mgr.c: _pre_lcd_off(1426) > [_pre_lcd_off:1426] Will LCD OFF as wake_up_setting[1]
10-24 19:06:00.536+0900 E/STARTER (  741): scontext_util.c: scontext_util_handle_lock_state(64) > [scontext_util_handle_lock_state:64] wear state[0],bPossible [0]
10-24 19:06:00.536+0900 W/STARTER (  741): clock-mgr.c: _check_reserved_popup_status(321) > [_check_reserved_popup_status:321] Current reserved apps status : 0
10-24 19:06:00.536+0900 W/STARTER (  741): clock-mgr.c: _check_reserved_apps_status(357) > [_check_reserved_apps_status:357] Current reserved apps status : 0
10-24 19:06:00.766+0900 W/SHealthCommon(  841): SystemUtil.cpp: OnDeviceStatusChanged(1005) > [1;35mlcdState:3[0;m
10-24 19:06:00.766+0900 I/watchface-viewer(  818): viewer-feedback.cpp: DisplayStateChangedCb(151) > state[2] sDisplayStateNormal[0]
10-24 19:06:00.791+0900 W/STARTER (  741): clock-mgr.c: _on_lcd_signal_receive_cb(1659) > [_on_lcd_signal_receive_cb:1659] _on_lcd_signal_receive_cb, 1659, Post LCD off by [gesture]
10-24 19:06:00.791+0900 W/STARTER (  741): clock-mgr.c: _post_lcd_off(1558) > [_post_lcd_off:1558] LCD OFF as reserved app[(null)] alpm mode[0] charger[0]
10-24 19:06:00.791+0900 W/STARTER (  741): clock-mgr.c: _post_lcd_off(1565) > [_post_lcd_off:1565] Current reserved apps status : 0
10-24 19:06:00.791+0900 W/STARTER (  741): clock-mgr.c: _post_lcd_off(1583) > [_post_lcd_off:1583] raise homescreen after 20 sec. home_visible[0]
10-24 19:06:00.791+0900 E/ALARM_MANAGER(  741): alarm-lib.c: alarmmgr_add_alarm_withcb(1174) > trigger_at_time(20), start(24-10-2019, 19:06:21), repeat(1), interval(20), type(-1073741822)
10-24 19:06:00.796+0900 I/APP_CORE(  776): appcore-efl.c: __do_app(429) > [APP 776] Event: PAUSE State: RUNNING
10-24 19:06:00.796+0900 I/CAPI_APPFW_APPLICATION(  776): app_main.c: app_appcore_pause(202) > app_appcore_pause
10-24 19:06:00.796+0900 W/W_HOME  (  776): main.c: _appcore_pause_cb(694) > appcore pause
10-24 19:06:00.796+0900 W/W_HOME  (  776): event_manager.c: _app_pause_cb(383) > state: 1 -> 2
10-24 19:06:00.796+0900 W/W_HOME  (  776): event_manager.c: _state_control(194) > control:2, app_state:2 win_state:0(1) pm_state:0 home_visible:0 clock_visible:1 tutorial_state:0 editing : 0, home_clocklist:0, addviewer:0 scrolling : 0, powersaving : 0, apptray state : 0, apptray visibility : 1, apptray edit visibility : 0
10-24 19:06:00.796+0900 W/W_HOME  (  776): event_manager.c: _state_control(194) > control:0, app_state:2 win_state:0(1) pm_state:0 home_visible:0 clock_visible:1 tutorial_state:0 editing : 0, home_clocklist:0, addviewer:0 scrolling : 0, powersaving : 0, apptray state : 0, apptray visibility : 1, apptray edit visibility : 0
10-24 19:06:00.796+0900 W/W_HOME  (  776): event_manager.c: _state_control(194) > control:1, app_state:2 win_state:0(1) pm_state:0 home_visible:0 clock_visible:1 tutorial_state:0 editing : 0, home_clocklist:0, addviewer:0 scrolling : 0, powersaving : 0, apptray state : 0, apptray visibility : 1, apptray edit visibility : 0
10-24 19:06:00.796+0900 I/MESSAGE_PORT(  506): MessagePortIpcServer.cpp: OnReadMessage(739) > _MessagePortIpcServer::OnReadMessage
10-24 19:06:00.796+0900 I/MESSAGE_PORT(  506): MessagePortIpcServer.cpp: HandleReceivedMessage(578) > _MessagePortIpcServer::HandleReceivedMessage
10-24 19:06:00.796+0900 I/MESSAGE_PORT(  506): MessagePortStub.cpp: OnIpcRequestReceived(147) > MessagePort message received
10-24 19:06:00.796+0900 I/MESSAGE_PORT(  506): MessagePortStub.cpp: OnCheckRemotePort(115) > _MessagePortStub::OnCheckRemotePort.
10-24 19:06:00.796+0900 I/MESSAGE_PORT(  506): MessagePortService.cpp: CheckRemotePort(200) > _MessagePortService::CheckRemotePort
10-24 19:06:00.796+0900 I/MESSAGE_PORT(  506): MessagePortService.cpp: GetKey(358) > _MessagePortService::GetKey
10-24 19:06:00.796+0900 I/MESSAGE_PORT(  506): MessagePortService.cpp: CheckRemotePort(213) > Check a remote message port: [com.samsung.w-music-player.music-control-service:music-control-service-request-message-port]
10-24 19:06:00.796+0900 E/MESSAGE_PORT(  506): MessagePortService.cpp: CheckRemotePort(235) > _MessagePortService::CheckRemotePort() Failed: MESSAGEPORT_ERROR_MESSAGEPORT_NOT_FOUND
10-24 19:06:00.796+0900 I/MESSAGE_PORT(  506): MessagePortIpcServer.cpp: Send(847) > _MessagePortIpcServer::Stop
10-24 19:06:00.801+0900 E/MESSAGE_PORT(  776): MessagePortProxy.cpp: CheckRemotePort(379) > The remote message port (music-control-service-request-message-port) is not found.
10-24 19:06:00.801+0900 W/W_HOME  (  776): clock_shortcut.c: _request_with_message_port(118) > remote port does not exist
10-24 19:06:00.801+0900 W/AUL     (  776): launch.c: app_request_to_launchpad(268) > request cmd(0) to(com.samsung.w-music-player.music-control-service)
10-24 19:06:00.801+0900 W/AUL_AMD (  540): amd_request.c: __request_handler(645) > __request_handler: 0
10-24 19:06:00.806+0900 E/AUL_AMD (  540): amd_request.c: __request_handler(669) > no appinfo
10-24 19:06:00.806+0900 E/AUL_AMD (  540): amd_appinfo.c: appinfo_get_value(1150) > appinfo get value: Invalid argument, 9
10-24 19:06:00.806+0900 E/PKGMGR_INFO(  540): pkgmgrinfo_pkginfo.c: pkgmgrinfo_updateinfo_check_update(2505) > (pkgid == NULL) pkgid is NULL
10-24 19:06:00.806+0900 E/AUL_AMD (  540): amd_appinfo.c: appinfo_get_value(1150) > appinfo get value: Invalid argument, 28
10-24 19:06:00.806+0900 E/AUL_AMD (  540): amd_appinfo.c: appinfo_get_value(1150) > appinfo get value: Invalid argument, 27
10-24 19:06:00.806+0900 W/AUL_AMD (  540): amd_launch.c: _start_app(1713) > caller pid : 776
10-24 19:06:00.806+0900 E/AUL_AMD (  540): amd_launch.c: _start_app(1726) > no appinfo
10-24 19:06:00.806+0900 E/AUL_AMD (  540): amd_launch.c: __real_send(835) > send fail to client
10-24 19:06:00.806+0900 W/AUL     (  776): launch.c: app_request_to_launchpad(282) > request cmd(0) result(-13)
10-24 19:06:00.806+0900 E/CAPI_APPFW_APP_CONTROL(  776): app_control.c: app_control_error(138) > [app_control_send_launch_request] APP_NOT_FOUND(0xfef00021)
10-24 19:06:00.806+0900 W/W_HOME  (  776): clock_shortcut.c: _mp_messageport_register(150) > err = fef00021
10-24 19:06:00.831+0900 E/ALARM_MANAGER(  534): alarm-manager.c: __is_cached_cookie(230) > Find cached cookie for [741].
10-24 19:06:00.911+0900 E/ALARM_MANAGER(  534): alarm-manager-schedule.c: _alarm_next_duetime(509) > alarm_id: 979135125, next duetime: 1571911581
10-24 19:06:00.911+0900 E/ALARM_MANAGER(  534): alarm-manager.c: __alarm_add_to_list(485) > [alarm-server]: After add alarm_id(979135125)
10-24 19:06:00.911+0900 E/ALARM_MANAGER(  534): alarm-manager.c: __alarm_create(1050) > [alarm-server]:alarm_context.c_due_time(1571929200), due_time(1571911581)
10-24 19:06:00.911+0900 E/ALARM_MANAGER(  534): alarm-manager.c: __rtc_set(325) > [alarm-server]ALARM_CLEAR ioctl is successfully done.
10-24 19:06:00.911+0900 E/ALARM_MANAGER(  534): alarm-manager.c: __rtc_set(332) > Setted RTC Alarm date/time is 24-10-2019, 10:06:21 (UTC).
10-24 19:06:00.916+0900 E/ALARM_MANAGER(  534): alarm-manager.c: __rtc_set(347) > [alarm-server]RTC ALARM_SET ioctl is successfully done.
10-24 19:06:00.916+0900 E/ALARM_MANAGER(  534): alarm-manager.c: __save_module_log(1769) > The file is not ready.
10-24 19:06:00.921+0900 E/ALARM_MANAGER(  534): alarm-manager.c: __save_module_log(1769) > The file is not ready.
10-24 19:06:01.001+0900 W/SHealthCommon( 7977): SystemUtil.cpp: OnDeviceStatusChanged(1005) > [1;35mlcdState:3[0;m
10-24 19:06:01.001+0900 W/SHealthCommon( 1120): SystemUtil.cpp: OnDeviceStatusChanged(1005) > [1;35mlcdState:3[0;m
10-24 19:06:01.001+0900 W/LibServiceCommon( 1120): SHealthServiceController.cpp: OnSystemUtilLcdStateChanged(645) > [1;35m ###[0;m
10-24 19:06:01.001+0900 W/LibServiceCommon( 1120): ContinuousHrFeatureController.cpp: Stop(142) > [1;40;33mwas not running[0;m
10-24 19:06:01.306+0900 I/APP_CORE(  776): appcore-efl.c: __do_app(429) > [APP 776] Event: MEM_FLUSH State: PAUSED
10-24 19:06:03.321+0900 W/WATCH_CORE(  818): appcore-watch.c: __signal_context_handler(1219) > _signal_context_handler: type: 0, state: 3
10-24 19:06:03.321+0900 I/WATCH_CORE(  818): appcore-watch.c: __signal_context_handler(1236) > Call the time_tick_cb
10-24 19:06:03.321+0900 I/CAPI_WATCH_APPLICATION(  818): watch_app_main.c: _watch_core_time_tick(306) > _watch_core_time_tick
10-24 19:06:03.321+0900 E/watchface-loader(  818): watchface-loader.cpp: OnAppTimeTick(673) > 
10-24 19:06:03.321+0900 I/watchface-loader(  818): watchface-loader.cpp: OnAppTimeTick(684) > set force update!!
10-24 19:06:03.326+0900 E/wnoti-service(  872): wnoti-db-utility.c: context_wearonoff_status_cb(1781) > status changed from 1 to 2 
10-24 19:06:03.326+0900 W/wnotib  (  776): w-notification-board-broker-main.c: _wnb_context_wearonoff_changged_cb(456) > wearonoff_state: 2 from 1
10-24 19:06:03.331+0900 W/LibServiceCommon( 1120): ContextCommonProxy.cpp: OnContextWearEventCB(570) > [1;40;33mstatus changed [2][0;m
10-24 19:06:03.331+0900 E/WMS     (  537): wms_event_handler.c: _wms_event_handler_cb_wearonoff_monitor(23195) > wear_monitor_status update[0] = 1 -> 2
10-24 19:06:03.356+0900 W/LibServiceCommon( 1120): ContinuousHrFeatureController.cpp: OnWearOff(257) > [1;40;33m#[0;m
10-24 19:06:05.811+0900 I/APP_CORE(  776): appcore-efl.c: __do_app(429) > [APP 776] Event: MEM_FLUSH State: PAUSED
10-24 19:06:06.451+0900 W/CRASH_MANAGER( 8630): worker.c: worker_job(1205) > 060868373656e157191155
