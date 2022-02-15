# Settings
BUILD_PATH := .
OUTDIR     := $(BUILD_PATH)/out
OBJDIR     := $(OUTDIR)/obj
TARGET     := app
CFLAGS     := -Wall -Wextra -Wunused -std=c++17 -MMD -MP -c
CC         := g++
INCLUDES   := $(BUILD_PATH)

# Tools
ECHO   := @echo
MKDIR  := $(VERB)mkdir -p
RM     := $(VERB)rm -fr
CPPC   := ../cppcheck-2.7/cppcheck --enable=all *.cpp

vpath %.cpp $(BUILD_PATH)

# Object files, implicitly the source files
OBJS := $(addprefix $(OBJDIR)/, HiQMain.o HiQRobot.o HiQParser.o HiQTests.o)


$(OUTDIR):
	$(ECHO) "Creating $@..."
	$(MKDIR) $@

$(OBJDIR):
	$(ECHO) "Creating $@..."
	$(MKDIR) $@

$(OBJDIR)/%.o: %.cpp
	$(ECHO) "-- Compiling $@..."
	$(CC) $(CFLAGS) $< -o $@

all: $(OUTDIR)/$(TARGET)

$(OUTDIR)/$(TARGET): $(OUTDIR) $(OBJDIR) $(OBJS)
	$(ECHO) "--- Linking $@"
	$(CC) -I$(INCLUDES) $(OBJS) -o $@

clean:
	$(ECHO) "Removing build output..."
	$(RM) $(OUTDIR)

check:
	$(CPPC)

%.d:
TEST_DEPS = $(OBJS:.o=.d)
-include $(TEST_DEPS)
