prj = alge
prjsrc = $(prj)src

subdirs = prog

clean:
	$(RM) -f *~ $(prj).o $(prj).zip */*~ */*/*~ */a.out *.tmp
	-for d in $(subdirs); do ($(MAKE) -C $$d clean ); done
	-rstrip.py -R *.[ch] *.py *.ma *.txt README* *akefile

$(prjsrc).zip::
	git archive --format=zip -9 HEAD > $@

usbdir = /media/C3

usb: $(prjsrc).zip
	mv $(prjsrc).zip $(usbdir)/

