# 🌿 PlantCare

Sistema inteligente para monitoramento e cuidado de plantas domésticas, ajudando a manter sua saúde por meio de tecnologia simples e acessível.
---
## 🧩 Descrição do Problema

Muitas pessoas enfrentam dificuldades para manter suas plantas vivas e saudáveis.
Entre as principais causas estão regar demais ou de menos, falta ou excesso de luz solar e ausência de rotina de cuidados.

## 💡 Solução

O PlantCare propõe um sistema que monitora as condições da planta em tempo real e fornece alertas, diagnósticos e recomendações para manter o bem-estar das plantas.

Funcionalidades Principais

Monitoramento Inteligente: sensores medem umidade, temperatura e luz.

Análise de Saúde: diagnóstico de possíveis problemas e recomendações de cuidados.

Lembretes de Cuidados: alertas sobre rega e manutenção da planta.

## ⚙️ Ferramentas Oracle

O projeto utiliza:

Oracle Database: armazenamento seguro e escalável dos dados coletados.

Oracle APEX: interface web administrativa para visualização e gerenciamento das informações.

## 🌐 Aplicação de Conceitos IoT

Sensores de umidade, luminosidade e temperatura conectados via Wi-Fi ao microcontrolador ESP32.

Envio dos dados para o banco através de APIs REST.

Exibição em tempo real no Oracle APEX.

Uso de Machine Learning para gerar recomendações automáticas.

## 🔧 Funcionalidades Implementadas

Envio de dados IoT simulados: ESP32 envia leituras de temperatura, umidade do ar e solo para o broker MQTT a cada 10 segundos.

Fluxo Node-RED: recebe e exibe os dados publicados no broker.

API Java: cadastro de usuários, plantas e sensores.

Projeto .NET: sistema para cadastro e pesquisa de plantas.

Aplicativo Mobile: app com login, cadastro e integração à API Java.

Banco Oracle: armazenamento centralizado das informações.

## 👥 Público-Alvo

Pessoas que possuem ou desejam ter plantas em casa, além de empresas e comércios que buscam melhorar o ambiente com vegetação saudável
