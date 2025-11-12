FROM ubuntu:24.04
ARG USUARIO
RUN test $USUARIO || { echo 'Variable USUARIO no definida; ejecute: "docker build --build-arg USUARIO=$USER -t ASI/image ."'; exit 1; }
ARG DEBIAN_FRONTEND=noninteractive
RUN  apt-get -y update && \
     apt-get install -y nano && \
     apt-get install -y openssh-server && \
     apt-get install -y sudo && \
     useradd -ms /bin/bash $USUARIO && \
     usermod -aG sudo $USUARIO && \
     echo "$USUARIO:$USUARIO" | chpasswd && \
     mkdir -p /home/$USUARIO/.ssh && \
     chown "$USUARIO:$USUARIO" /home/$USUARIO/.ssh && \
     chmod 700 /home/$USUARIO/.ssh && \
     sed  -i -e 's/^%sudo/#&/' -e '$a%sudo ALL=(ALL) NOPASSWD: ALL' /etc/sudoers && \
     sed  -i -e '$asudo service ssh status >/dev/null 2>&1 || sudo service ssh start >/dev/null 2>&1' /home/$USUARIO/.bashrc

USER $USUARIO
WORKDIR /home/$USUARIO
CMD ["bash"]
