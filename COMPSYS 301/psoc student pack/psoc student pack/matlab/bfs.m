%% Breath First Search

function [retmap,retvisited,retsteps] = bfs(mapfile,startlocation,targetlocation)
    % 1. Start by putting any one of the graph's vertices at the back of a queue.
    % 2. Take the front item of the queue and add it to the visited list.
    % 3. Create a list of that vertex's adjacent nodes. Add the ones which 
    %    aren't in the visited list to the back of the queue.
    % 4. Keep repeating steps 2 and 3 until the queue is empty.

end

%% Placing steps on map
function placestep(position,i)
    % This function will plot a insert yellow rectangle and also print a number in this rectangle. Use with plotmap/viewmap. 
    position = [16-position(1) position(2)];
    position=[position(2)+0.1 position(1)+0.1];
    rectangle('Position',[position,0.8,0.8],'FaceColor','y');
    c=sprintf('%d',i);
    text(position(1)+0.2,position(2)+0.2,c,'FontSize',10);
end