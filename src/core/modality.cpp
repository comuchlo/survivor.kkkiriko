#include "modality.hpp"

Modality::Modality() {
    modalityType = ModalityType::NONE;
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
