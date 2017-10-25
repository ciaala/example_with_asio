SHELL:=bash
export DOCUMENT:=cppugzh_asio

QPDF:=$(shell command -v qpdf 2>/dev/null)
VENV:=$(shell command -v virtualenv 2>/dev/null)

.PHONY: all clean dist-clean

all: copy
	@echo "Build complete!"
	@echo	"PDF located at: '$(shell pwd)/generated/pdf/$(DOCUMENT).pdf'"

clean:
	@echo "Cleaning LaTeX artifacts..."
	@$(MAKE) SHELL=$(SHELL) -C latex clean
	@echo "Removing generated PDF files..."
	@rm -f generated/pdf/*.pdf

dist-clean: clean
	@echo "Cleaning virtualenv..."
	@rm -rf python/env
	@echo "Removing untracked files..."
	@git clean -fdx &>/dev/null

compile: dirs virtualenv
	@echo "Building LaTeX document..."
	@source python/env/bin/activate && $(MAKE) SHELL=$(SHELL) -C latex

copy: compile
ifdef QPDF
	@echo $(QPDF)
	@echo "Linearizing PDF..."
	@qpdf --linearize latex/.build/$(DOCUMENT).pdf generated/pdf/$(DOCUMENT).pdf
else
	@echo "Copying PDF..."
	@cp latex/.build/$(DOCUMENT).pdf generated/pdf
endif

dirs:
	@mkdir -p generated/pdf

virtualenv:
ifdef VENV
	@test -d python/env || (echo "Initializing virtualenv..." && \
		$(VENV) python/env && \
		python/env/bin/pip install -Ur python/requirements.txt)
else
	$(error "missing dependency: virtualenv!")
endif
