%% Dijkstra's Algorithm

function [retmap,retvisited,retsteps] = dfs(mapfile,startlocation,targetlocation)
    % for each vertex v in a map
        % distance[v]  = infinite
        % previous[v] = null
        % if vertex is not 

end


function placestep(position,i)
    % This function will plot a insert yellow rectangle and also print a number in this rectangle. Use with plotmap/viewmap. 
    position = [16-position(1) position(2)];
    position=[position(2)+0.1 position(1)+0.1];
    rectangle('Position',[position,0.8,0.8],'FaceColor','y');
    c=sprintf('%d',i);
    text(position(1)+0.2,position(2)+0.2,c,'FontSize',10);
end