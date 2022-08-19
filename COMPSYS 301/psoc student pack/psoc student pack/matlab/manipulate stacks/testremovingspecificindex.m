
cell = {[1,2],[3,4],[5,6]};
ew =pop1(cell,2);
disp(ew)
size(ew)
function[array]= pop1(poparray,index)
% Input index has to be a integer
    array = poparray;
    array(index)= [];

end
