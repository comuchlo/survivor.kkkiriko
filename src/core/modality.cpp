#include "modality.hpp"

Modality::Modality() {
    this->modalityType = ModalityType::NONE;
}

Modality::~Modality() {
};

void Modality::drawModality() {

}

void Modality::drawEndModality() {

}

ControllerExitCode Modality::handleModality() {
    return ControllerExitCode::CONTINUE;
}

bool Modality::shouldExit() {
    return true;
};
