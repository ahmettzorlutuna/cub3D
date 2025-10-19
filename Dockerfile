# Basit, küçük ve hızlı taban imaj
FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# Sistem + build bağımlılıkları + X sunucu araçları
RUN apt-get update && apt-get install -y \
    build-essential cmake make gcc g++ git curl wget \
    xz-utils ca-certificates \
    x11-apps x11vnc xvfb fluxbox \
    python3 python3-pip \
    libx11-dev libxext-dev libbsd-dev zlib1g-dev \
    # noVNC & websockify bağımlılığı
    websockify \
 && rm -rf /var/lib/apt/lists/*

# noVNC (statik dosyalar)
RUN mkdir -p /opt/novnc && \
    curl -L https://github.com/novnc/noVNC/archive/refs/tags/v1.5.0.tar.gz | tar xz --strip-components=1 -C /opt/novnc && \
    ln -s /opt/novnc/vnc.html /opt/novnc/index.html

# Çalışma dizini: uygulaman (kub3d kodun) buraya bind edilecek
WORKDIR /app

# Başlangıç betiği
COPY start.sh /usr/local/bin/start.sh
RUN chmod +x /usr/local/bin/start.sh

# noVNC (HTTP) + WebSocket portu
EXPOSE 6080

# Varsayılan: noVNC başlat, Xvfb aç, VNC servis et, sonra uygulamayı çalıştır
CMD ["/usr/local/bin/start.sh"]
