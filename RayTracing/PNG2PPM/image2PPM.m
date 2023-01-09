% SABIR ILYASS
% function creates a PPM image from an image given at the input
function image2PPM(image, path1, path2)

globalPath = strcat(path1, "/", path2);

[l, c, channels] = size(image);

if channels == 3
    im = zeros(c,l, channels);
    im(:,:,1) = image(:,:,1)';
    im(:,:,2) = image(:,:,2)';
    im(:,:,3) = image(:,:,3)';


else
    im = image';
end

mkdir(path1)
edit (globalPath)

writelines("P3",globalPath);
writelines(int2str(l) + " " + int2str(c),globalPath,WriteMode="append");
writelines("255",globalPath,WriteMode="append");

if channels == 1
    for j = 1:l
        for i = 1:c
           writelines(int2str(im(i,j)) + " " + int2str(im(i,j)) + " " + int2str(im(i,j)), globalPath,WriteMode="append");
        end
    end
end

if channels == 3
    for j = 1:l
        for i = 1:c
           writelines(int2str(im(i,j, 1)) + " " + int2str(im(i,j, 2)) + " " + int2str(im(i,j, 3)), globalPath,WriteMode="append");
        end
    end
end 




