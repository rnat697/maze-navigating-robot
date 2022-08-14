
cell = {[1,2],[3,4],[5,6]};
[array,val]=pop1(cell)


function[array, value]= pop1(poparray)
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
        array{1,i} = poparray{1,i}
    end

end