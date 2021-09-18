clean_stuff := ./*/a.out ./a.out ./*/.vscode/

clean:
	rm -rf $(clean_stuff)
