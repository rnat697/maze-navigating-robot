
cell = {[1,2],[3,4],[5,6]};
array = [2,2];
putontop(cell,array)

% puts node ontop top of stack and push all back
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