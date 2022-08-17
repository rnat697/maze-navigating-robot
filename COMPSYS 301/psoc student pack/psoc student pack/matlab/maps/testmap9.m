%% Function descriptions
%% To view a map, given a map file

viewmap('map_10.txt',0); % shows walls
viewmap('map_10.txt',1); % shows track

%or else

[m]=map_convert('map_10.txt');
plotmap(m);
%Here   'm' is the map file returned as a matrix
startloc= [7,1]; %map 9, 13,1  map 10 7,1
targetloc=[1,12]; %map 9, 1,17  map 10 1,12
 
% Your simulations will use this structure
[m,v,s]=dfs(m,[startloc],[targetloc]);
%Here   'm' is the map file returned as a matrix
%       'v' is a matrix that shows which cells have been visited, '0' means
%       visited, '1' means not visited
%       's' is the vector of steps to reach the target,
%       [startloc] is a vector i.e. [2,2]
%       [targetloc] is also a vector ie [4,18]

%To view the path determined above use 
%plotmap(m,s);
