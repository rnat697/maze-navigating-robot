%% Appending to the end of the stack

stack = {[5,2], [5,4]};
stack = queue(stack, [3,4])

function [updatedStack] = queue(stack,location)
    updatedStack = stack;
    updatedStack{length(stack)+1} = location

end