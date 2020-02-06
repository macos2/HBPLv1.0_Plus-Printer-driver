PREFIX:=/usr
all:foo2hbpl1-plus foo2hbpl1-plus-wrapper

foo2hbpl1-plus:foo2hbpl1-plus.c hbplv1_template.c hbplv1_encode.c
	@echo "\e[32mBuild foo2hbpl1-plus\e[0m"
	@gcc foo2hbpl1-plus.c hbplv1_template.c hbplv1_encode.c  -o foo2hbpl1-plus -lm -O2 -w

foo2hbpl1-plus-wrapper:foo2hbpl1-plus-wrapper.in
	@echo "\e[32mModify foo2hbpl1-plus-wrapper\e[0m"
	@sed "6cPREFIX=$(PREFIX)"  foo2hbpl1-plus-wrapper.in >foo2hbpl1-plus-wrapper

install:foo2hbpl1-plus foo2hbpl1-plus-wrapper
	@echo "\e[34mInstall Binary File\e[0m"
	@mkdir -p $(PREFIX)/bin
	@cp foo2hbpl1-plus-wrapper $(PREFIX)/bin
	@cp foo2hbpl1-plus $(PREFIX)/bin
	@chmod 0755 $(PREFIX)/bin/foo2hbpl1-plus-wrapper $(PREFIX)/bin/foo2hbpl1-plus
	@echo "\e[34mInstall PPD File\e[0m"
	@mkdir -p $(PREFIX)/share/ppd/hbplv1-plus
	@cp ppd/* $(PREFIX)/share/ppd/hbplv1-plus
	@chmod 0644 $(PREFIX)/share/ppd/hbplv1-plus/*
	@echo "\e[34mInstall ICM File\e[0m"
	@mkdir -p $(PREFIX)/share/foo2hbplv1-plus/icm
	@cp icm/* $(PREFIX)/share/foo2hbplv1-plus/icm
	@chmod 0644 $(PREFIX)/share/foo2hbplv1-plus/icm/*

uninstall:
	@echo "\e[31mUninstall...\e[0m"
	@rm -f $(PREFIX)/bin/foo2hbpl1-plus-wrapper
	@rm -f $(PREFIX)/bin/foo2hbpl1-plus
	@rm -r -f $(PREFIX)/share/ppd/hbplv1-plus
	@rm -r -f $(PREFIX)/share/foo2hbplv1-plus

clean:
	@echo "\e[31mClean...\e[0m"
	@rm -f foo2hbpl1-plus-wrapper
	@rm -f foo2hbpl1-plus
