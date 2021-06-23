FROM denismakogon/opencv3-slim:edge

# Install necessary components
COPY    . /src/
WORKDIR /src/
ENV     DEBIAN_FRONTEND=noninteractive FLASK_APP=src/server.py FLASK_RUN_PORT=5678
RUN     pip install --no-cache --no-cache-dir --upgrade -r requirements.txt; \
        rm -fr ~/.cache/pip /tmp*;

CMD     flask run