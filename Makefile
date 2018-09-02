
.PHONY: build
build:
	pio run

.PHONY: verbose
verbose:
	pio run -v

.PHONY: flash
flash:
	pio run --target upload

.PHONY: clean
clean:
	pio run --target clean
