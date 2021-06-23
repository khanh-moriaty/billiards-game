MAKE = make

all:
	cd client && $(MAKE) all_

run:
	cd client && $(MAKE) run_

install:
	cd client && $(MAKE) install_

clean:
	cd client && $(MAKE) clean