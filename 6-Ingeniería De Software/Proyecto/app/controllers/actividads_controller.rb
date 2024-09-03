class ActividadsController < ApplicationController
  def index
    @actividads = Actividad.all
  end


  def show
    @actividad = Actividad.find(params[:id])
  end

  def new
    @actividad = current_user.actividads.build
  end

  def edit
    @actividad = Actividad.find(params[:id])
  end

  def create
    @actividad = current_user.actividads.build(actividad_params)
    @actividad.user = current_user
    if @actividad.save
      redirect_to actividads_path
    else
      render :new, status: :unprocessable_entity
    end
  end

  def update
    @actividad = Actividad.find(params[:id])
    if @actividad.update(actividad_params)
      redirect_to actividads_path
    else
      render :edit, status: :unprocessable_entity
    end
  end

  def destroy
    @actividad = Actividad.find(params[:id])
    @actividad.destroy
    redirect_to actividads_path, status: :see_other
  end

  private

  def actividad_params
    params.require(:actividad).permit(:titulo, :cantidad_personas, :precio, :fecha)
  end

end
