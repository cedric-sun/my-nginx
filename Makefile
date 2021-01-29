
default:	build

clean:
	rm -rf Makefile objs

build:
	$(MAKE) -f objs/Makefile

install:
	$(MAKE) -f objs/Makefile install

modules:
	$(MAKE) -f objs/Makefile modules

upgrade:
	/home/cesun/nginx-src/install/sbin/nginx -t

	kill -USR2 `cat /home/cesun/nginx-src/install/logs/nginx.pid`
	sleep 1
	test -f /home/cesun/nginx-src/install/logs/nginx.pid.oldbin

	kill -QUIT `cat /home/cesun/nginx-src/install/logs/nginx.pid.oldbin`
