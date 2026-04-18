CXX = g++
CXXFLAGS = -Wall

# Final executable
pa3: main.o Model.o GameCommand.o View.o Mage.o ManaSpire.o DemonHideout.o Building.o GameObject.o Point2D.o Vector2D.o
	$(CXX) $(CXXFLAGS) -o pa3 main.o Model.o GameCommand.o View.o Mage.o ManaSpire.o DemonHideout.o Building.o GameObject.o Point2D.o Vector2D.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Model.o: Model.cpp
	$(CXX) $(CXXFLAGS) -c Model.cpp

GameCommand.o: GameCommand.cpp
	$(CXX) $(CXXFLAGS) -c GameCommand.cpp

View.o: View.cpp
	$(CXX) $(CXXFLAGS) -c View.cpp

Mage.o: Mage.cpp
	$(CXX) $(CXXFLAGS) -c Mage.cpp

ManaSpire.o: ManaSpire.cpp
	$(CXX) $(CXXFLAGS) -c ManaSpire.cpp

DemonHideout.o: DemonHideout.cpp
	$(CXX) $(CXXFLAGS) -c DemonHideout.cpp

Building.o: Building.cpp
	$(CXX) $(CXXFLAGS) -c Building.cpp

GameObject.o: GameObject.cpp
	$(CXX) $(CXXFLAGS) -c GameObject.cpp

Point2D.o: Point2D.cpp
	$(CXX) $(CXXFLAGS) -c Point2D.cpp

Vector2D.o: Vector2D.cpp
	$(CXX) $(CXXFLAGS) -c Vector2D.cpp

# Checkpoint targets for testing
Checkpoint3: Test3.o Mage.o ManaSpire.o DemonHideout.o Building.o GameObject.o Point2D.o Vector2D.o
	$(CXX) $(CXXFLAGS) -o Checkpoint3 Test3.o Mage.o ManaSpire.o DemonHideout.o Building.o GameObject.o Point2D.o Vector2D.o

Test3.o: Test3.cpp
	$(CXX) $(CXXFLAGS) -c Test3.cpp

Checkpoint1: TestCheckpoint1.o Point2D.o Vector2D.o
	$(CXX) $(CXXFLAGS) -o Checkpoint1 TestCheckpoint1.o Point2D.o Vector2D.o

TestCheckpoint1.o: TestCheckpoint1.cpp
	$(CXX) $(CXXFLAGS) -c TestCheckpoint1.cpp

Checkpoint2: TestCheckpoint2.o ManaSpire.o DemonHideout.o Building.o GameObject.o Point2D.o Vector2D.o
	$(CXX) $(CXXFLAGS) -o Checkpoint2 TestCheckpoint2.o ManaSpire.o DemonHideout.o Building.o GameObject.o Point2D.o Vector2D.o

TestCheckpoint2.o: TestCheckpoint2.cpp
	$(CXX) $(CXXFLAGS) -c TestCheckpoint2.cpp

clean:
	rm -f *.o pa3 Checkpoint1 Checkpoint2 Checkpoint3
