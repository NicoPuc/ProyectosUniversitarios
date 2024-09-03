class RequestsController < ApplicationController
  before_action :set_request, only: [:destroy, :accept, :reject, :show, :edit, :update]
#  before_action :set_actividad, only: [:create]
#  before_action :check_owner, only: [:accept, :reject]

  def index
    @requests = current_user.requests
  end

  def show
  end

  def new
    @request = current_user.requests.build
  end

  def edit
  end

  def create
    #@request = Request.new(request_params)
    @actividad = Actividad.find(request_params[:actividad_id])
    @request = current_user.requests.build(request_params)

    #@request.user = current_user
    @request.actividad = @actividad
    @request.fecha = @actividad.fecha
    @request.status = "pending"

  
    if @actividad.user == current_user
      redirect_to requests_path, alert: 'No puedes hacer una solicitud a tu propia actividad.'
    elsif @request.save
      redirect_to requests_path, notice: 'La solicitud de actividad fue creada exitosamente.'
    else
      puts @request.errors.full_messages
        render :new, status: :unprocessable_entity
    end
  end

  def update
    if @request.update(request_params)
      redirect_to requests_path, notice: 'La solicitud de actividad fue actualizada exitosamente.'
    else
      render :edit, status: :unprocessable_entity
    end
  end

  def destroy
    @request = current_user.requests.find(params[:id])
    @request.destroy
    redirect_to requests_path, notice: 'La solicitud de actividad fue cancelada exitosamente.'
  end

  # Método para aceptar una solicitud de actividad
  def accept
    @request = Request.find(params[:id])
    if @request.update(status: "accepted")
      # Crear una nueva participación
      Participation.create(user_id: @request.user_id, actividad_id: @request.actividad_id)
      redirect_back(fallback_location: requests_path, notice: "Solicitud aceptada.")
    else
      redirect_back(fallback_location: requests_path, notice: "Hubo un error al aceptar la solicitud.")
    end
  end
  
  # Método para rechazar una solicitud de actividad
  def reject
    @request = Request.find(params[:id])
    if @request.update(status: "rejected")
      # Eliminar la solicitud
      @request.destroy
      redirect_back(fallback_location: requests_path, notice: "Solicitud rechazada.")
    else
      redirect_back(fallback_location: requests_path, notice: "Hubo un error al rechazar la solicitud.")
    end
  end

  # Método para mostrar las solicitudes de actividad enviadas por el usuario actual
  def sent
    @sent_requests = Request.where(user_id: current_user.id)
  end      

  private

  def set_request
    @request = Request.find(params[:id])
  end

  def set_actividad
    @actividad = Actividad.find(params[:actividad_id])
  end

  def check_owner
    unless @request.actividad.user == current_user
      redirect_to actividads_path, alert: 'No tienes permiso para aceptar o rechazar esta solicitud.'
    end
  end

  def request_params
    params.require(:request).permit(:actividad_id, :description)
  end
end