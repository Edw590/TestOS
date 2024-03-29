// Copyright 2022 DADi590
//
// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include "../CLibs/stdio.h"
#include "Pic.h"
#include "Keyboard/Keyboard.h"

void interruptHandler(uint32_t irq) {
	if (irq == 1) {
		keyboardInterruptHandler();
	} else {
		printf("Interrupt detected. IRQ %u\n", irq);
	}

	sendEOI((uint8_t) irq); // Send the EOI command to the PIC
}

void exceptionHandlerNoErr(uint32_t exc_num) {
	printf("Exception detected. Number: %u\n", exc_num);

	sendEOI((uint8_t) exc_num); // Send the EOI command to the PIC
}

void exceptionHandlerErr(uint32_t exc_num, uint32_t err_code) {
	printf("Exception detected. Number: %u. Error code: %u\n", exc_num, err_code);

	if (exc_num == 13) {
		__asm__ volatile ("cli; hlt"); // Completely hangs the computer
	}

	sendEOI((uint8_t) exc_num); // Send the EOI command to the
}
