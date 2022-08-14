visiting = [1,2]

yloc = visiting(1)
xloc = visiting(2)
checkingNextPos = {[yloc,xloc],[yloc,xloc],[yloc,xloc],[3,4]};

% 2. in another loop Compare location of N,S,E,W using the retmap

% checks if hitting the left border
if (xloc > 1)
 checkingNextPos{1,1}=[yloc,xloc-1] %move left
end

% checks if hitting the right border
if (xloc < mapsize(2))
    checkingNextPos{1,3}=[yloc,xloc+1]; %move right
end

% checks if hitting the bottom border
if (yloc < mapsize(1))
 checkingNextPos(1,2)=[yloc+1,xloc]; % move down
end