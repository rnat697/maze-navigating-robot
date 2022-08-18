%% Breath First Search

function [retmap,retvisited,retsteps] = bfs(mapfile,startlocation,targetlocation)
    % 1. Start by putting any one of the graph's vertices at the back of a queue.
    % 2. Take the front item of the queue and add it to the visited list.
    % 3. Create a list of that vertex's adjacent nodes. Add the ones which 
    %    aren't in the visited list to the back of the queue.
    % 4. Keep repeating steps 2 and 3 until the queue is empty.
    
        
    queue = {startlocation};
    mapsize = size(mapfile);
    retvisited= ones(mapsize);
    
    %init visiting to starting node.
    visiting = startlocation;  
    retsteps = {startlocation};
    
    retmap = mapfile; %original map that was provided.
    index = 1;
    checkifAtEnd =0;
    
   %init array with 4 local values based on location
   yloc = visiting(1);
   xloc = visiting(2);
   checkingNextPos = {[yloc,xloc],[yloc,xloc],[yloc,xloc],[yloc,xloc]};
    while (checkifAtEnd ~= 1)
        
        % 2. Compare location of N,S,E,W using the retmap
        
        % checks if hitting the left border
        if (xloc > 1)
            checkingNextPos{1,1}=[yloc,xloc-1]; %move left
        else
            checkingNextPos{1,1}=[-1,-1]; % no position available
        end
        
        % checks if hitting the right border
        if (xloc < mapsize(2))
            checkingNextPos{1,3}=[yloc,xloc+1]; %move right
         else
            checkingNextPos{1,3}=[-1,-1];   
        end
        
        % checks if hitting the bottom border
        if (yloc < mapsize(1))  
         checkingNextPos{1,2}=[yloc+1,xloc]; % move down
         else
            checkingNextPos{1,2}=[-1,-1];
        end
        
        %checks if hitting the top border
        if(yloc > 1)    
            checkingNextPos{1,4}=[yloc-1,xloc]; %move up
         else
            checkingNextPos{1,4}=[-1,-1];   
        end
        
        
         for i=1:4
            position = checkingNextPos{1,i};
            row = position(1);
            col = position(2);

            % checks if its a valid location
            if((row ~= -1 || col ~= -1))

                % checks map file to see if its a path (0) and not a wall(1)
                % and checks retvisited map to see location has not been 
                % visited(1) [visited = 0 in retvisited map]
                if (mapfile(row,col)==0 && retvisited(row,col) == 1 )   %space detected ready to look
                    queue = append(queue,position);
     
                end
            end
        end      % to add to queue
        
        visiting = queue{1,1};    %select visting as top of stack
        retsteps = append(retsteps,visiting);
        queue = popstack(queue); % removes location at top of stack
        
        
        % 5. update retvisited map file based on visited location
        %update for next iteration
        yloc = visiting(1);
        xloc = visiting(2);
        
        % 6. update node value
        index = index +1;   % index of steps

         % 1.place step on the map
        retvisited(yloc,xloc)=0;
        placestep(retsteps{1,index},index);
        
        %checks if location of node is at end
        checkifAtEnd =(targetlocation(1) == visiting(1)) && (targetlocation(2) == visiting(2));
        disp(visiting)
        
    end
    
    display(retsteps)

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
%% Appends to end of stack
function [updatedStack] = append(stack,node)
    updatedStack = stack;
    updatedStack{length(stack)+1} = node;

end

%% removes top node on the stack
function[array]= popstack(poparray)
    array={1,length(poparray)-1};
    poparray{1,1}= [0,0];
    
    x = length(poparray);

    %takes array
    for i= 2:x
        value = poparray{1,i};
        poparray{1,i-1}= value;  
    end

    %cuts array
    for i= 1:x-1
        array{1,i} = poparray{1,i};
    end
end

%% puts node on top of stack and push all other nodes back
function[output]= putontop(cell,array)
    %array is node wanting to be put
    %cell is the full stack(queue)
    output={1,length(cell)+1};
    output{1,1}= array;
    
    x = length(cell);

    %takes array
    for i = 1:x
        output{1,i+1}=cell{1,i};
    end
end

