mac-swap-screens : mac-swap-screens.c Makefile
	clang -o mac-swap-screens -framework CoreGraphics mac-swap-screens.c

clean:
	rm mac-swap-screens
