TEXROOTS=203.tex

OUTPUTS=$(TEXROOTS:.tex=.pdf)
DEPS=$(TEXROOTS:.tex=.d)

#ifeq ("$(wildcard bib/csrg.bib)","")
#$(error "Please update the bib submodule: git submodule update --init --recursive")
#endif

all: $(OUTPUTS)

-include $(DEPS)

%.pdf: %.tex
	latexmk -pdf -M -MF $(DEPS) $<

clean:
	$(RM) *.dvi *.bbl *.blg *.aux *.fls *.log *.fdb_latexmk $(DEPS) *.out *.def *.ques

spotless: clean
	$(RM) $(OUTPUTS)

.PHONY: clean spotless all
