From ubuntu:23.04

WORKDIR /bomberman

COPY . .

RUN apt-get -y update && apt-get install -y libsfml-dev libirrlicht-dev g++ make

RUN make

CMD ./bomberman
