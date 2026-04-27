CXX = g++
CXXFLAGS = -Wall

# Output directory
OUT_DIR = output

# Create directory if it doesn't exist
$(shell mkdir -p $(OUT_DIR))

# Object files with path prefix
OBJS = $(OUT_DIR)/main.o $(OUT_DIR)/Model.o $(OUT_DIR)/GameCommand.o $(OUT_DIR)/View.o \
       $(OUT_DIR)/Mage.o $(OUT_DIR)/ManaSpire.o $(OUT_DIR)/DemonHideout.o \
       $(OUT_DIR)/Building.o $(OUT_DIR)/GameObject.o $(OUT_DIR)/Point2D.o \
       $(OUT_DIR)/Vector2D.o $(OUT_DIR)/RoamingDemon.o

# Final executable
$(OUT_DIR)/pa4: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Pattern rule for object files
$(OUT_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Checkpoint targets
$(OUT_DIR)/Checkpoint3: $(OUT_DIR)/Test3.o $(OUT_DIR)/Mage.o $(OUT_DIR)/ManaSpire.o \
                        $(OUT_DIR)/DemonHideout.o $(OUT_DIR)/Building.o \
                        $(OUT_DIR)/GameObject.o $(OUT_DIR)/Point2D.o $(OUT_DIR)/Vector2D.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OUT_DIR)/Checkpoint1: $(OUT_DIR)/TestCheckpoint1.o $(OUT_DIR)/Point2D.o $(OUT_DIR)/Vector2D.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OUT_DIR)/Checkpoint2: $(OUT_DIR)/TestCheckpoint2.o $(OUT_DIR)/ManaSpire.o \
                        $(OUT_DIR)/DemonHideout.o $(OUT_DIR)/Building.o \
                        $(OUT_DIR)/GameObject.o $(OUT_DIR)/Point2D.o $(OUT_DIR)/Vector2D.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Convenience targets (without path prefix)
pa4: $(OUT_DIR)/pa4
Checkpoint1: $(OUT_DIR)/Checkpoint1
Checkpoint2: $(OUT_DIR)/Checkpoint2
Checkpoint3: $(OUT_DIR)/Checkpoint3

clean:
	rm -rf $(OUT_DIR)

.PHONY: pa4 Checkpoint1 Checkpoint2 Checkpoint3 clean

# CXX = g++
# CXXFLAGS = -Wall

# # Final executable
# pa4: main.o Model.o GameCommand.o View.o Mage.o ManaSpire.o DemonHideout.o Building.o GameObject.o Point2D.o Vector2D.o RoamingDemon.o
# 	$(CXX) $(CXXFLAGS) -o pa4 main.o Model.o GameCommand.o View.o Mage.o ManaSpire.o DemonHideout.o Building.o GameObject.o Point2D.o Vector2D.o RoamingDemon.o

# main.o: main.cpp
# 	$(CXX) $(CXXFLAGS) -c main.cpp

# Model.o: Model.cpp
# 	$(CXX) $(CXXFLAGS) -c Model.cpp

# GameCommand.o: GameCommand.cpp
# 	$(CXX) $(CXXFLAGS) -c GameCommand.cpp

# View.o: View.cpp
# 	$(CXX) $(CXXFLAGS) -c View.cpp

# Mage.o: Mage.cpp
# 	$(CXX) $(CXXFLAGS) -c Mage.cpp

# ManaSpire.o: ManaSpire.cpp
# 	$(CXX) $(CXXFLAGS) -c ManaSpire.cpp

# DemonHideout.o: DemonHideout.cpp
# 	$(CXX) $(CXXFLAGS) -c DemonHideout.cpp

# Building.o: Building.cpp
# 	$(CXX) $(CXXFLAGS) -c Building.cpp

# GameObject.o: GameObject.cpp
# 	$(CXX) $(CXXFLAGS) -c GameObject.cpp

# Point2D.o: Point2D.cpp
# 	$(CXX) $(CXXFLAGS) -c Point2D.cpp

# Vector2D.o: Vector2D.cpp
# 	$(CXX) $(CXXFLAGS) -c Vector2D.cpp

# RoamingDemon.o: RoamingDemon.cpp
# 	$(CXX) $(CXXFLAGS) -c RoamingDemon.cpp

# # Checkpoint targets for testing
# Checkpoint3: Test3.o Mage.o ManaSpire.o DemonHideout.o Building.o GameObject.o Point2D.o Vector2D.o
# 	$(CXX) $(CXXFLAGS) -o Checkpoint3 Test3.o Mage.o ManaSpire.o DemonHideout.o Building.o GameObject.o Point2D.o Vector2D.o

# Test3.o: Test3.cpp
# 	$(CXX) $(CXXFLAGS) -c Test3.cpp

# Checkpoint1: TestCheckpoint1.o Point2D.o Vector2D.o
# 	$(CXX) $(CXXFLAGS) -o Checkpoint1 TestCheckpoint1.o Point2D.o Vector2D.o

# TestCheckpoint1.o: TestCheckpoint1.cpp
# 	$(CXX) $(CXXFLAGS) -c TestCheckpoint1.cpp

# Checkpoint2: TestCheckpoint2.o ManaSpire.o DemonHideout.o Building.o GameObject.o Point2D.o Vector2D.o
# 	$(CXX) $(CXXFLAGS) -o Checkpoint2 TestCheckpoint2.o ManaSpire.o DemonHideout.o Building.o GameObject.o Point2D.o Vector2D.o

# TestCheckpoint2.o: TestCheckpoint2.cpp
# 	$(CXX) $(CXXFLAGS) -c TestCheckpoint2.cpp

# clean:
# 	rm -f *.o pa4 Checkpoint1 Checkpoint2 Checkpoint3
