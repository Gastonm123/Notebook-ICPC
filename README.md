# Notebook para ICPC

Contenedor de algoritmos propios, contribuciones a otros notebook populares como *El Vasito*, *El Diego* y *La pandilla*.

## Compilar notebook

Instalar el paquete de idioma español para babel
```
sudo apt-get install texlive-lang-spanish
```

Instalar pdflatex y compilar _main.tex_
```
sudo apt install texlive-latex-base
pdflatex main.tex
```

o instalar xelatex y compilarlo con mejores fuentes
```
sudo apt install texlive-xetex
xelatex main.tex
```

Si surge algún error, intentar borrar todos los archivos creados por latex y volver a intentar.