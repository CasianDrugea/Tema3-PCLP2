FROM jokeswar/base-ctl:latest

RUN echo "Hello from Docker"

COPY ./checker ${CHECKER_DATA_DIRECTORY}
