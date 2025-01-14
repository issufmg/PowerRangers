# PowerRangers
# Sistema de Gestão para Restaurantes

Este projeto em C++ é um sistema de gestão para restaurantes, desenvolvido para atender as principais necessidades operacionais de um restaurante. Ele abrange funcionalidades como gerenciamento de cardápio, controle de mesas, estoque, pedidos, funcionários, clientes, e muito mais.

## Estrutura do Projeto

O sistema é organizado em diversas classes, cada uma representando uma funcionalidade ou parte essencial do restaurante:

### 1. **Cardápio**
- Gerencia os itens disponíveis para os clientes.
- Subclasses:
  - **Bebida**: Gerencia as bebidas disponíveis.
  - **Comida**: Gerencia os pratos principais.
  - **Sobremesa**: Gerencia as sobremesas.
  - **Porções**: Gerencia os aperitivos e porções disponíveis.

### 2. **Estoque**
- Controla os insumos e materiais do restaurante.
- Subclasses:
  - **Estoque Frio**: Gerencia itens que precisam de refrigeração.
  - **Estoque Quente**: Gerencia itens que não requerem refrigeração.

### 3. **Controle de Mesa**
- Responsável por gerenciar a ocupação e o status das mesas.

### 4. **Pedido**
- Gerencia os pedidos realizados pelos clientes, incluindo os itens selecionados e status do preparo.

### 5. **Conta**
- Controla o fechamento da conta, incluindo cálculos de taxas e impostos.

### 6. **Funcionários**
- Gerencia os dados e informações dos funcionários.

### 7. **Clientes**
- Registra as informações dos clientes, incluindo histórico de pedidos.

### 8. **Delivery**
- (Opcional) Gerencia pedidos para entrega, incluindo endereço e status da entrega.

### 9. **Promoções/Prato do Dia**
- Permite a configuração de promoções especiais ou pratos do dia.

### 10. **Relatório**
- Gera relatórios de vendas, consumo de estoque e outras métricas importantes.

### 11. **Garçom**
- Gerencia as tarefas e dados dos garçons, incluindo os pedidos atendidos.

## Tecnologias Utilizadas
- Linguagem: C++
- Paradigma: Programação Orientada a Objetos (POO)

## Como Usar
1. **Clone o Repositório:**
   ```bash
   git clone <URL do repositório>
   ```
2. **Compile o Código:**
   Utilize um compilador de C++, como g++.
   ```bash
   g++ main.cpp -o restaurante
   ```
3. **Execute o Programa:**
   ```bash
   ./restaurante
   ```


