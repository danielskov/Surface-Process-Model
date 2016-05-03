for i=1:nx
    for j=1:ny
        if(drain_area(j,i)>mean(drain_area(:)) && diff(j,i)>0)
            disp('lol')
        end
    end
end