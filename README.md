# XiaoZhi-like Voice Assistant for ESP32-2432S028 (Nguyễn Sơn, dark theme)

This project is a ready-to-upload template for GitHub that will build a firmware binary (.bin) using GitHub Actions (PlatformIO).
- Board: ESP32-2432S028
- Theme: Dark, cute face icons
- Voice: Male (North VN, age 30-40) -- TTS placeholder (configure your API key)
- UI: chat messages + expressive face icons

## How to use
1. Create a new GitHub repository.
2. Upload all files from this ZIP into the repository root (Commit).
3. On GitHub, go to Actions -> Run workflow (Build ESP32 Firmware). Wait for the workflow to complete.
4. Download artifact `esp32-firmware.zip` from the workflow run, extract `firmware.bin`.
5. Flash `firmware.bin` using esptool-js web flasher: https://esphome.github.io/esp-web-tools/

## Configure TTS/STT
Edit `src/voice_config.h` to add your API key and startup greeting.
