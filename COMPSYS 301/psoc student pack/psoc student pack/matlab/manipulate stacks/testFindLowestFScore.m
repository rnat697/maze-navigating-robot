Fscore = {6,3,5,7,2,5,8};

prevFscore = 2000;
    for i = 1:length(Fscore)
        nodeFscore = Fscore{1,i};
        if nodeFscore < prevFscore
            smallestFNode = [1,i];
            prevFscore = nodeFscore
        end
        
    end
    disp(smallestFNode)