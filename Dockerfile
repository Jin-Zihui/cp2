FROM gcc:10
WORKDIR /app/
COPY ./* ./
RUN gcc main.c -o main.out
RUN chmod +x main.out