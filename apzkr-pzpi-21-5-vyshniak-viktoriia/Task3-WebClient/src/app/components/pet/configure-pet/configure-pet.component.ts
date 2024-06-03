import { Component, Inject, Input, inject } from '@angular/core';
import { FormBuilder, FormGroup } from '@angular/forms';
import { Guid } from 'guid-typescript';
import { PetService } from '../../../core/services/pet.service';
import { L10N_LOCALE } from 'angular-l10n';
import { NgbActiveModal } from '@ng-bootstrap/ng-bootstrap';

@Component({
	selector: 'app-configure-pet',
	templateUrl: './configure-pet.component.html',
	styleUrl: './configure-pet.component.scss'
})
export class ConfigurePetComponent {
	@Input()
	petId!: Guid;

	@Input()
	onSaveCallback!: Function;

	configurePetDeviceForm!: FormGroup;
	activeModal = inject(NgbActiveModal);

	locale: any;

	constructor(
		private fb: FormBuilder,
		private petService: PetService,
		@Inject(L10N_LOCALE) locale: any
	) {
		this.locale = locale;
	}

	ngOnInit(): void {
		this.initConfigurePetForm();
		this.initPet();
	}

	initConfigurePetForm(): void {
		this.configurePetDeviceForm = this.fb.group({
			arduinoSettingsId: this.petId,
			petDeviceIpAddress: '',
			wifiSettings: this.fb.group({
				ssid: [''],
				password: ['']
			})
		});
	}

	configurePetDevice(): void {
		this.petService.configurePetDevice(this.configurePetDeviceForm.value).subscribe({
			next: (response) => {
				this.configurePetDeviceForm.value.petDeviceIpAddress = response.ipAddress;
				this.onSaveCallback();
				this.activeModal.close();
			}
		});
	}

	initPet() {
		this.petService.getPetSettingsById(this.petId).subscribe(settings => {
			this.configurePetDeviceForm.patchValue(settings);
		});
	}
}
