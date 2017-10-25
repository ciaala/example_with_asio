.PHONY: all clean dirs pdf

all: pdf

clean:
	@latexmk -CA -output-directory=.build &>/dev/null
	@rm -rf .build/_minted-$(DOCUMENT)

dirs:
	@mkdir -p .build

pdf: dirs $(DOCUMENT).tex
	@latexmk -output-directory=.build \
					 -pdf \
					 -pdflatex="xelatex --shell-escape -interaction=errorstopmode" \
					 $(DOCUMENT)

