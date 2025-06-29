<div align="center">
    <br />
    <p>
        <img src="https://github.com/user-attachments/assets/6efa0534-0ebc-4a1b-96e3-2f4623edb46e" title="SHEDD" alt="SHEDD System" width="1000" />
    </p>
    <br />
    <p>
        <a href="https://github.com/jchicatti/C-Star">
            <img src="https://github.com/user-attachments/assets/d5448ff5-cb7e-4209-8d41-2eba074bfb13" alt="C-Star Repo" height="50"/>
        </a>
        <a href="#english-version">
            <img src="https://github.com/user-attachments/assets/dde1b0cd-6cd6-49df-8f42-c1dc258b7af9" alt="English" height="50"/>
        </a>
        <a href="#versión-en-español">
            <img src="https://github.com/user-attachments/assets/bae907f2-e41a-401e-a67e-1f6a63b66179" alt="Español" height="50"/>
        </a>
    </p>
</div>

# SHEDD – Server Heartbeat Diagnostic and Defibrillator

## English version

The SHEDD system is designed to enable automatic recovery of servers that may hang due to OS or service-level failures. This repository is structured in thematic folders:

The `OS Setup` folder contains scripts and registry files to ensure the server can reboot without human intervention. It includes Windows `.reg` and `.bat` files to disable Windows Hello, enable AutoAdminLogon, disable Windows Update services and prevent the boot recovery screen. All configuration is done via the Registry Editor, Local Group Policy Editor, and services.msc. Equivalent instructions for Linux systems are provided through systemd service files which ensure autostart and disable interactive recovery modes.

The `Circuit` folder provides a connection guide with clear diagrams showing how to wire the Arduino board, relay, RTC, push button, and power control pins.

The `Firmware` folder contains the main Arduino program and the ping-monitoring scripts. The `Unit Tests` subfolder includes individual Arduino sketches for testing each physical component. These allow step-by-step validation of each piece of hardware during assembly.

This repository assumes administrator access to the machine and is intended for educational or local deployment scenarios.

---

## Versión en español

Este repositorio contiene todo lo necesario para configurar, probar y desplegar el subsistema SHEDD: una solución de recuperación automática de bajo costo para servidores educativos o personales.

El contenido se encuentra dividido en carpetas temáticas:

La carpeta `OS Setup` incluye los scripts y archivos de configuración para asegurar que el sistema operativo pueda recuperarse sin intervención manual tras un reinicio. Contiene archivos `.reg` y `.bat` que desactivan Windows Hello, habilitan el inicio de sesión automático (AutoAdminLogon), desactivan las actualizaciones automáticas y la recuperación automática tras errores de arranque. Estas configuraciones se aplican desde el Editor del Registro, el Editor de directivas de grupo local y services.msc. También se incluyen instrucciones equivalentes para sistemas Linux basadas en systemd, las cuales permiten el arranque automático de los servicios y desactivan mecanismos de recuperación interactiva.

La carpeta `Circuit` contiene la guía de conexión con el diagrama completo del sistema, indicando los pines de conexión al botón físico, al relé y a la motherboard.

La carpeta `Firmware` contiene el programa principal del Arduino y los scripts de monitoreo por ping. En la subcarpeta `Unit Tests` se incluyen programas individuales para probar cada uno de los componentes del sistema: relé, botón, RTC, y otros. Estos programas funcionan como un tutorial paso a paso para ensamblar y verificar el hardware.

Este repositorio asume acceso de administrador a la máquina y está destinado a escenarios de implementación locales o educativos.
