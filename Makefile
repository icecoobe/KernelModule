DIRS = HelloWorld TestProcEntry ReadWriteProc FileSystem ListPractise ListPractise ModuleParam PrintPid VFS

all:
	$(foreach dir,$(DIRS),$(MAKE) -C $(dir);)

clean:
	$(foreach dir,$(DIRS),$(MAKE) clean -C $(dir);)
