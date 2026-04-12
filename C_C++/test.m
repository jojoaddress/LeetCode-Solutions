function neighborNodes = getNeighborNodes(rows,cols,index,field)
[row,col] = ind2sub([rows,cols],index);
neighborNodes = inf(8,2);

direction = [-1,-1; -1,0; -1,1; 0,-1; 0,1; 1,-1; 1,0; 1,1];
for i=1:8
    newRow = row + direction(i,1);
    newCol = col + direction(i,2);
    if newRow > 0 && newRow<=rows && newCol > 0 && newCol <=cols
        child_sub = [newRow,newCol];
        child_index = sub2ind([rows,cols],newRow,newCol);
        neighborNodes(i,1) = child_index;
        if field(newRow, newCol)~=2
            cost = norm(child_sub - [row,col]);
            neighborNodes(i,2) = cost;
        end

    end
end