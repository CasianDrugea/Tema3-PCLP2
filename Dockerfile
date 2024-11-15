FROM ghcr.io/open-education-hub/vmcheker-next-base-image/base-container:latest

RUN echo "Hello from Docker"

COPY ./checker ${CHECKER_DATA_DIRECTORY}
