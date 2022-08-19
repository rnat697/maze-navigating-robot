%% Function descriptions
%% To view a map, given a map file

viewmap('map_8.txt',0); % shows walls
viewmap('map_8.txt',1); % shows track

%or else

[m]=map_convert('map_8.txt');
plotmap(m);
%Here   'm' is the map file returned as a matrix
startloc= [14,1];
targetloc=[1,18];

[Fmaps]=scoremap(m,[targetloc],startloc);
display("map done")


