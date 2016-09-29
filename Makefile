all:
	cd tests && make -f Makefile

.PHONY: clean
clean:
	-rm -f tests/*Test */*.out *.out *~ */*~
