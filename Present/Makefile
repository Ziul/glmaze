# É só escrever o comando "make". Entro com "make clean" para limpar a sujeira e
# "make buildclean" para deletar o pdf '\newcommand{\blackandwhite}{true}\input{test.tex}'

all: main.pdf

# Compila a cada alteração de qualquer arquivo *.tex ou de qualquer *.vhd dentro da pasta 'src'
main.pdf: *.tex clean
	clear
#	pdflatex -interaction errorstopmode -interaction=batchmode main.tex
	pdflatex main.tex
	clear
	@echo "Compilado pela primeira vez...Feito."
#	make bib
	@echo "Compilando pela segunda vez:"
	@pdflatex -interaction=batchmode main.tex
	@echo -n "Feito\nCompilando pela ultima vez:\n"
	@pdflatex -interaction=batchmode main.tex
	@echo -n "Limpando sujeira..."
	@make clean
	@echo "Feito."
	pdfopt main.pdf $(notdir $(PWD)).pdf
	@echo "Informações do arquivo gerado:" $(notdir $(PWD)).pdf
	pdfinfo $(notdir $(PWD)).pdf
	rm -rf main.pdf
	
# Limpa qualquer sujeira que reste após compilação
# Útil que objetos de linguagens são incluidos e ficam relatando erros após retirados.
clean:
	rm -rf *.aux *.log *.toc *.bbl *.bak *.blg *.out *.lof *.lot *.snm *.nav
	
buildclean:
	rm -rf *.pdf
	
# Por algum motivo o *.pdf sumia da pasta. Gerado apenas para guardar uma copia de segurança na pasta
backup: main.pdf
	pdfopt main.pdf $(notdir $(PWD)).pdf

bib: *.bib *.tex
	if test -f *.bib ;\
	then \
		echo -n "Buscando citações";\
		grep -v "\%" *.tex > search.temp;\
		if grep '\\cite{'  search.temp -qn;\
		then \
			echo " ";\
			echo -n "Montando bibliografias..." ;\
			bibtex main -terse;\
			echo "Feito.";\
		else \
			echo " ... Nenhuma encontrada";\
		fi;\
	else \
		echo "Arquivo de bibliografias inexistente.";\
	fi;
	rm -rf search.temp

configure:
#	if test -d fts; then echo "hello world!";else echo "Not find!"; fi
	grep -v "\%" *.tex > search.temp
	grep '\\cite{'  search.temp
	rm -rv search.temp
#	grep '^%' *.tex
	
.SILENT:
