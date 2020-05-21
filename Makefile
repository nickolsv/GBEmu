CC  = g++
HDIR = -I'.header'
CFLAGS = $(HDIR)

# Executable Names
OUT = gbEMU
TESTOUT = gbTEST

# Directories
SRCDIR  = src
OBJDIR  = obj
TESTDIR	= tests

# All Source Files
SRC  = $(wildcard $(SRCDIR)/*.cpp)
TEST = $(wildcard $(TESTDIR)/*.cpp)

# Get all Object Filenames (One Object File for each Source File)
OBJ = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))
TESTOBJ = $(patsubst $(TESTDIR)/%.cpp, $(OBJDIR)/%.o, $(TEST))


## RULES ##

# Compile object files into executable
$(OUT): $(OBJDIR) $(OBJDIR)/$(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

$(TESTOUT): $(OBJDIR) $(OBJDIR)/$(OBJ)  $(OBJDIR)/$(TESTOBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(TESTOBJ)


# Compile each object file using its corresponding source file
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

# Create directory containing object files
$(OBJDIR):
	mkdir $@


clean:
	$(RM) $(OBJDIR)/*.o
	rmdir $(OBJDIR)
	$(RM) $(OUT)
	$(RM) $(TESTOUT)