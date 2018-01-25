#Copyright (c) 2015 Benjamin Pylko

#This program is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.

#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.

#You should have received a copy of the GNU General Public License
#along with this program.  If not, see <http://www.gnu.org/licenses/>.

AT = @
INCDIR = -I$(HOME)/wpilib/cpp/current/include -I$(HOME)/wpilib/user/cpp/include
CPPFLAGS += -g -Wall -W $(INCDIR) -std=c++14 -fPIC 
LFLAGS = -L$(HOME)/wpilib/cpp/current/lib -L$(HOME)/wpilib/user/cpp/lib -lCTRLib -lwpi
CXX = arm-frc-linux-gnueabi-g++
TEAM = 5572
RMCOMMAND = rm -f
DEPLOYTARGET = roboRIO-$(TEAM)-FRC.local

SOURCES = $(wildcard src/*.cpp)
HEADERS = $(wildcard src/*.hpp)
OBJECTS = $(patsubst src/%.cpp,src/%.o,$(wildcard src/*.cpp))



all: $(OBJECTS)
	test -d bin/ || mkdir -p bin/
	$(CXX) $(CPPFLAGS) $(OBJECTS) $(LFLAGS) -o bin/FRCUserProgram
clean:
	@for dir in src; do find $$dir -name \*.o -exec $(RMCOMMAND) {} \; ; done
	$(RMCOMMAND) bin/*
	
deploy:
	ssh lvuser$(AT)$(DEPLOYTARGET) "rm /home/lvuser/FRCUserProgram || true"
	sftp -oBatchMode=no -b sftpbatchfile lvuser$(AT)$(DEPLOYTARGET)
	ssh lvuser$(AT)$(DEPLOYTARGET) ". /etc/profile.d/natinst-path.sh; chmod a+x /home/lvuser/FRCUserProgram; /usr/local/frc/bin/frcKillRobot.sh -t -r"

kill-robot:
	ssh lvuser$(AT)$(DEPLOYTARGET) "/usr/local/frc/bin/frcKillRobot.sh"
