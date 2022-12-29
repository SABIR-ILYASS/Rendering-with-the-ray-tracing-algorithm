% SABIR ILYASS
function image2PPM(image, path1, path2)


globalPath = strcat(path1, "/", path2);

im = image';
[l, c, channels] = size(im);
mkdir(path1)
edit (globalPath)

writelines("P3",globalPath);
writelines(int2str(l) + " " + int2str(c),globalPath,WriteMode="append");
writelines("255",globalPath,WriteMode="append");

if channels == 1
    for j = 1:c
        for i = 1:l
           writelines(int2str(im(i,j)) + " " + int2str(im(i,j)) + " " + int2str(im(i,j)), globalPath,WriteMode="append");
        end
    end
end

if channels == 3
    for j = 1:c
        for i = 1:l
           writelines(int2str(im(i,j, 1) + " " + int2str(im(i,j, 2) + " " + int2str(im(i,j, 3)))), globalPath,WriteMode="append");
        end
    end
end 




