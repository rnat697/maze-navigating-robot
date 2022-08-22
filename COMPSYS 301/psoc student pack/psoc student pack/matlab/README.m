%% Function descriptions
%% To view a map, given a map file

viewmap('map_2.txt',0); % shows walls
viewmap('map_2.txt',1); % shows track

%or else

[m]=map_convert('map_2.txt');
plotmap(m);
%Here   'm' is the map file returned as a matrix
startloc= [2,2];
targetloc=[14,8];

% Your simulations will use this structure
[m,v,s]=astar(m,[startloc],[targetloc]);
%Here   'm' is the map file returned as a matrix
%       'v' is a matrix that shows which cells have been visited, '0' means
%       visited, '1' means not visited
%       's' is the vector of steps to reach the target,
%       [startloc] is a vector i.e. [2,2]
%       [targetloc] is also a vector ie [4,18]

%To view the path determined above use 
%plotmap(m,s);

