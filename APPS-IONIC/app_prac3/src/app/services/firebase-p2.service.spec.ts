import { TestBed } from '@angular/core/testing';

import { FirebaseP2Service } from './firebase-p2.service';

describe('FirebaseP2Service', () => {
  beforeEach(() => TestBed.configureTestingModule({}));

  it('should be created', () => {
    const service: FirebaseP2Service = TestBed.get(FirebaseP2Service);
    expect(service).toBeTruthy();
  });
});
