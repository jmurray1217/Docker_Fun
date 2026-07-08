# ---------- Build Stage ----------
FROM alpine:latest AS builder

RUN apk add --no-cache g++ make

WORKDIR /app
COPY . .
RUN make LDFLAGS="-static"

# ---------- Runtime Stage ----------
FROM alpine:latest

WORKDIR /app
COPY --from=builder /app/myapp .

CMD ["./myapp"]
LABEL Name=dockerfun Version=0.0.1