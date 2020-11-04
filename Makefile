all:
	jlc-kicad-tools -v --warn-no-lcsc-partnumber -d cpl_rotation_db `pwd`
	
clean:
	rm -rf *.csv *.pos *.xml *.drl *.gbr *.ps *.zip *.net *.d356
