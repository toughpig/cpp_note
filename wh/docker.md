docker login
docker pull pagl1acc1/ubuntu:fmt
docker images
docker run -it pagl1acc1/ubuntu:fmt /bin/bash
exit
docker ps -a
docker stop container-id
docker start container-id
docker rm -f container-id
docker commit -m="msg" -a="author" container-id new-image-name
docker rmi image-id